/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2018, Alliance for Sustainable Energy, LLC. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#include "../ForwardTranslator.hpp"
#include "../../model/Model.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/Schedule_Impl.hpp"
#include "../../model/AirLoopHVAC.hpp"
#include "../../model/AirLoopHVAC_Impl.hpp"
#include "../../model/Node.hpp"
#include "../../model/Node_Impl.hpp"
#include "../../model/ThermalZone.hpp"
#include "../../model/ThermalZone_Impl.hpp"
#include "../../model/ZoneHVACWaterToAirHeatPump.hpp"
#include "../../model/ZoneHVACWaterToAirHeatPump_Impl.hpp"
#include "../../model/FanOnOff.hpp"
#include "../../model/FanOnOff_Impl.hpp"
#include "../../model/CoilCoolingWaterToAirHeatPumpEquationFit.hpp"
#include "../../model/CoilCoolingWaterToAirHeatPumpEquationFit_Impl.hpp"
#include "../../model/CoilHeatingWaterToAirHeatPumpEquationFit.hpp"
#include "../../model/CoilHeatingWaterToAirHeatPumpEquationFit_Impl.hpp"
#include "../../model/CoilHeatingElectric.hpp"
#include "../../model/CoilHeatingElectric_Impl.hpp"
#include "../../model/CoilHeatingGas.hpp"
#include "../../model/CoilHeatingGas_Impl.hpp"
#include "../../model/CoilHeatingWater.hpp"
#include "../../model/CoilHeatingWater_Impl.hpp"
#include <utilities/idd/ZoneHVAC_WaterToAirHeatPump_FieldEnums.hxx>
#include <utilities/idd/OutdoorAir_Mixer_FieldEnums.hxx>
#include <utilities/idd/Fan_OnOff_FieldEnums.hxx>
#include <utilities/idd/Fan_ConstantVolume_FieldEnums.hxx>
#include <utilities/idd/Coil_Cooling_WaterToAirHeatPump_EquationFit_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_WaterToAirHeatPump_EquationFit_FieldEnums.hxx>
#include <utilities/idd/Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFit_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFit_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Fuel_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Electric_FieldEnums.hxx>
#include <utilities/idd/Coil_Heating_Water_FieldEnums.hxx>
#include "../../utilities/idd/IddEnums.hpp"
#include "../../utilities/math/FloatCompare.hpp"
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/IddFactory.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

boost::optional<IdfObject> ForwardTranslator::translateZoneHVACWaterToAirHeatPump(
    ZoneHVACWaterToAirHeatPump& modelObject)
{
  boost::optional<std::string> s;
  boost::optional<double> value;

  IdfObject idfObject(IddObjectType::ZoneHVAC_WaterToAirHeatPump);

  m_idfObjects.push_back(idfObject);

  // Name
  std::string baseName = modelObject.name().get();

  idfObject.setName(baseName);

  std::string mixedAirNodeName = baseName + " Mixed Air Node";

  std::string coolingCoilOutletNodeName = baseName + " Cooling Coil Outlet Node";

  std::string heatingCoilOutletNodeName = baseName + " Heating Coil Outlet Node";

  std::string fanOutletNodeName = baseName + " Fan Outlet Node";

  std::string reliefAirNodeName = baseName + " Relief Air Node";

  std::string oaNodeName = baseName + " OA Node";

  std::string airInletNodeName;
  if( auto node = modelObject.inletNode() ) {
    airInletNodeName = node->nameString();
  }

  std::string airOutletNodeName;
  if( auto node = modelObject.outletNode() ) {
    airOutletNodeName = node->nameString();
  }

  auto translateMixer = [&]() {
    auto t_airLoopHVAC = modelObject.airLoopHVAC();
    if( t_airLoopHVAC ) {
      return false;
    }

    bool zeroOA = false;
    if( (value = modelObject.outdoorAirFlowRateDuringCoolingOperation()) ) {
      zeroOA = equal(value.get(),0.0);
    }
    if( (value = modelObject.outdoorAirFlowRateDuringHeatingOperation()) ) {
      zeroOA = (zeroOA && equal(value.get(),0.0));
    }
    if( (value = modelObject.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded()) ) {
      zeroOA = (zeroOA && equal(value.get(),0.0));
    }

    if( zeroOA ) return false;

    return true;
  };

  // AvailabilityScheduleName
  if( boost::optional<Schedule> schedule = modelObject.availabilitySchedule() )
  {
    if( boost::optional<IdfObject> _schedule = translateAndMapModelObject(schedule.get()) )
    {
      idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::AvailabilityScheduleName,_schedule->name().get());
    }
  }

  // AirInletNodeName
  idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::AirInletNodeName,airInletNodeName);

  // AirOutletNodeName
  idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::AirOutletNodeName,airOutletNodeName);

  // Outdoor Air Mixer
  if( translateMixer() ) {
    std::string oaMixerName = baseName + " OA Mixer";

    IdfObject _outdoorAirMixer(IddObjectType::OutdoorAir_Mixer);
    _outdoorAirMixer.setName(oaMixerName);
    m_idfObjects.push_back(_outdoorAirMixer);

    _outdoorAirMixer.setString(OutdoorAir_MixerFields::MixedAirNodeName,mixedAirNodeName);

    _outdoorAirMixer.setString(OutdoorAir_MixerFields::OutdoorAirStreamNodeName,oaNodeName);

    IdfObject _oaNodeList(openstudio::IddObjectType::OutdoorAir_NodeList);
    _oaNodeList.setString(0,oaNodeName);
    m_idfObjects.push_back(_oaNodeList);

    _outdoorAirMixer.setString(OutdoorAir_MixerFields::ReliefAirStreamNodeName,reliefAirNodeName);

    _outdoorAirMixer.setString(OutdoorAir_MixerFields::ReturnAirStreamNodeName,airInletNodeName);

    // OutdoorAirMixerObjectType
    idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::OutdoorAirMixerObjectType,
                        _outdoorAirMixer.iddObject().name());

    // OutdoorAirMixerName
    idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::OutdoorAirMixerName,oaMixerName);
  }

  // SupplyAirFlowRateDuringCoolingOperation
  if( modelObject.isSupplyAirFlowRateDuringCoolingOperationAutosized() )
  {
    idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::CoolingSupplyAirFlowRate,"Autosize");
  }
  else if( (value = modelObject.supplyAirFlowRateDuringCoolingOperation()) )
  {
    idfObject.setDouble(ZoneHVAC_WaterToAirHeatPumpFields::CoolingSupplyAirFlowRate,value.get());
  }

  // SupplyAirFlowRateDuringHeatingOperation
  if( modelObject.isSupplyAirFlowRateDuringHeatingOperationAutosized() )
  {
    idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::HeatingSupplyAirFlowRate,"Autosize");
  }
  else if( (value = modelObject.supplyAirFlowRateDuringHeatingOperation()) )
  {
    idfObject.setDouble(ZoneHVAC_WaterToAirHeatPumpFields::HeatingSupplyAirFlowRate,value.get());
  }

  // SupplyAirFlowRateWhenNoCoolingorHeatingisNeeded
  if( modelObject.isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() )
  {
    idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRate,"Autosize");
  }
  else if( (value = modelObject.supplyAirFlowRateWhenNoCoolingorHeatingisNeeded()) )
  {
    idfObject.setDouble(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadSupplyAirFlowRate,value.get());
  }

  // OutdoorAirFlowRateDuringCoolingOperation
  if( modelObject.isOutdoorAirFlowRateDuringCoolingOperationAutosized() )
  {
    idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::CoolingOutdoorAirFlowRate,"Autosize");
  }
  else if( (value = modelObject.outdoorAirFlowRateDuringCoolingOperation()) )
  {
    idfObject.setDouble(ZoneHVAC_WaterToAirHeatPumpFields::CoolingOutdoorAirFlowRate,value.get());
  }

  // OutdoorAirFlowRateDuringHeatingOperation
  if( modelObject.isOutdoorAirFlowRateDuringHeatingOperationAutosized() )
  {
    idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::HeatingOutdoorAirFlowRate,"Autosize");
  }
  else if( (value = modelObject.outdoorAirFlowRateDuringHeatingOperation()) )
  {
    idfObject.setDouble(ZoneHVAC_WaterToAirHeatPumpFields::HeatingOutdoorAirFlowRate,value.get());
  }

  // OutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded
  if( modelObject.isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() )
  {
    idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadOutdoorAirFlowRate,"Autosize");
  }
  else if( (value = modelObject.outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded()) )
  {
    idfObject.setDouble(ZoneHVAC_WaterToAirHeatPumpFields::NoLoadOutdoorAirFlowRate,value.get());
  }

  // SupplyAirFanObjectType and Name
  HVACComponent supplyAirFan = modelObject.supplyAirFan();

  if( boost::optional<IdfObject> _supplyAirFan = translateAndMapModelObject(supplyAirFan) )
  {
    idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFanObjectType,_supplyAirFan->iddObject().name() );

    idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFanName,_supplyAirFan->name().get());

    if( istringEqual(modelObject.fanPlacement(),"BlowThrough") ) {
      if( translateMixer() ) {
        if( _supplyAirFan->iddObject().type() == IddObjectType::Fan_ConstantVolume )
        {
          _supplyAirFan->setString(Fan_ConstantVolumeFields::AirInletNodeName,mixedAirNodeName);
          _supplyAirFan->setString(Fan_ConstantVolumeFields::AirOutletNodeName,fanOutletNodeName);
        }
        else if( _supplyAirFan->iddObject().type() == IddObjectType::Fan_OnOff )
        {
          _supplyAirFan->setString(Fan_OnOffFields::AirInletNodeName,mixedAirNodeName);
          _supplyAirFan->setString(Fan_OnOffFields::AirOutletNodeName,fanOutletNodeName);
        }
      } else {
        if( _supplyAirFan->iddObject().type() == IddObjectType::Fan_ConstantVolume )
        {
          _supplyAirFan->setString(Fan_ConstantVolumeFields::AirInletNodeName,airInletNodeName);
          _supplyAirFan->setString(Fan_ConstantVolumeFields::AirOutletNodeName,fanOutletNodeName);
        }
        else if( _supplyAirFan->iddObject().type() == IddObjectType::Fan_OnOff )
        {
          _supplyAirFan->setString(Fan_OnOffFields::AirInletNodeName,airInletNodeName);
          _supplyAirFan->setString(Fan_OnOffFields::AirOutletNodeName,fanOutletNodeName);
        }
      }
    } else {
      if( _supplyAirFan->iddObject().type() == IddObjectType::Fan_ConstantVolume )
      {
        _supplyAirFan->setString(Fan_ConstantVolumeFields::AirInletNodeName,heatingCoilOutletNodeName);
        _supplyAirFan->setString(Fan_ConstantVolumeFields::AirOutletNodeName,fanOutletNodeName);
      }
      else if( _supplyAirFan->iddObject().type() == IddObjectType::Fan_OnOff )
      {
        _supplyAirFan->setString(Fan_OnOffFields::AirInletNodeName,heatingCoilOutletNodeName);
        _supplyAirFan->setString(Fan_OnOffFields::AirOutletNodeName,fanOutletNodeName);
      }
    }
  }

  // HeatingCoilObjectType and Name
  HVACComponent heatingCoil = modelObject.heatingCoil();

  if( boost::optional<IdfObject> _heatingCoil = translateAndMapModelObject(heatingCoil) )
  {
    idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::HeatingCoilObjectType,_heatingCoil->iddObject().name() );

    idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::HeatingCoilName,_heatingCoil->name().get() );

    if( _heatingCoil->iddObject().type() == IddObjectType::Coil_Heating_WaterToAirHeatPump_EquationFit ) {
      _heatingCoil->setString(Coil_Heating_WaterToAirHeatPump_EquationFitFields::AirInletNodeName,coolingCoilOutletNodeName);
      _heatingCoil->setString(Coil_Heating_WaterToAirHeatPump_EquationFitFields::AirOutletNodeName,heatingCoilOutletNodeName);
    } else if( _heatingCoil->iddObject().type() == IddObjectType::Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFit ) {
      _heatingCoil->setString(Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::IndoorAirInletNodeName,coolingCoilOutletNodeName);
      _heatingCoil->setString(Coil_Heating_WaterToAirHeatPump_VariableSpeedEquationFitFields::IndoorAirOutletNodeName,heatingCoilOutletNodeName);
    }
  }

  // CoolingCoilObjectType and Name
  HVACComponent coolingCoil = modelObject.coolingCoil();

  if( boost::optional<IdfObject> _coolingCoil = translateAndMapModelObject(coolingCoil) )
  {
    std::string coolingCoilInletNodeName;

    if( istringEqual(modelObject.fanPlacement(),"BlowThrough") ) {
      coolingCoilInletNodeName = fanOutletNodeName;
    } else {
      if( translateMixer() ) {
        coolingCoilInletNodeName = mixedAirNodeName;
      } else {
        coolingCoilInletNodeName = airInletNodeName;
      }
    }

    idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::CoolingCoilObjectType,_coolingCoil->iddObject().name() );

    idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::CoolingCoilName,_coolingCoil->name().get() );

    if( _coolingCoil->iddObject().type() == IddObjectType::Coil_Cooling_WaterToAirHeatPump_EquationFit) {
      _coolingCoil->setString(Coil_Cooling_WaterToAirHeatPump_EquationFitFields::AirInletNodeName,coolingCoilInletNodeName);
      _coolingCoil->setString(Coil_Cooling_WaterToAirHeatPump_EquationFitFields::AirOutletNodeName,coolingCoilOutletNodeName);
    } else if( _coolingCoil->iddObject().type() == IddObjectType::Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFit ) {
      _coolingCoil->setString(Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::IndoorAirInletNodeName,coolingCoilInletNodeName);
      _coolingCoil->setString(Coil_Cooling_WaterToAirHeatPump_VariableSpeedEquationFitFields::IndoorAirOutletNodeName,coolingCoilOutletNodeName);
    }
  }

  //Maximum Cycling Rate
  if( (value = modelObject.maximumCyclingRate()) )
  {
    idfObject.setDouble(ZoneHVAC_WaterToAirHeatPumpFields::MaximumCyclingRate,value.get());
  }

  //Heat Pump Time Constant
  if( (value = modelObject.heatPumpTimeConstant()) )
  {
    idfObject.setDouble(ZoneHVAC_WaterToAirHeatPumpFields::HeatPumpTimeConstant,value.get());
  }

  //Fraction of On-Cycle Power Use
  if( (value = modelObject.fractionofOnCyclePowerUse()) )
  {
    idfObject.setDouble(ZoneHVAC_WaterToAirHeatPumpFields::FractionofOnCyclePowerUse,value.get());
  }

  //Heat Pump Fan Delay Time
  if( (value = modelObject.heatPumpFanDelayTime()) )
  {
    idfObject.setDouble(ZoneHVAC_WaterToAirHeatPumpFields::HeatPumpFanDelayTime,value.get());
  }

  // SupplementalHeatingCoilObjectType and SupplementalHeatingCoilName
  HVACComponent supplementalHeatingCoil = modelObject.supplementalHeatingCoil();

  if( boost::optional<IdfObject> _supplementalHeatingCoil = translateAndMapModelObject(supplementalHeatingCoil) )
  {
    idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::SupplementalHeatingCoilObjectType,_supplementalHeatingCoil->iddObject().name() );

    idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::SupplementalHeatingCoilName,_supplementalHeatingCoil->name().get() );

    if( istringEqual(modelObject.fanPlacement(),"BlowThrough")  ) {
      if( _supplementalHeatingCoil->iddObject().type() == IddObjectType::Coil_Heating_Fuel )
      {
        _supplementalHeatingCoil->setString(Coil_Heating_FuelFields::AirInletNodeName,heatingCoilOutletNodeName);

        _supplementalHeatingCoil->setString(Coil_Heating_FuelFields::AirOutletNodeName,airOutletNodeName);
      }
      else if( _supplementalHeatingCoil->iddObject().type() == IddObjectType::Coil_Heating_Electric )
      {
        _supplementalHeatingCoil->setString(Coil_Heating_ElectricFields::AirInletNodeName,heatingCoilOutletNodeName);

        _supplementalHeatingCoil->setString(Coil_Heating_ElectricFields::AirOutletNodeName,airOutletNodeName);
      }
      else if( _supplementalHeatingCoil->iddObject().type() == IddObjectType::Coil_Heating_Water )
      {
        _supplementalHeatingCoil->setString(Coil_Heating_WaterFields::AirInletNodeName,heatingCoilOutletNodeName);

        _supplementalHeatingCoil->setString(Coil_Heating_WaterFields::AirOutletNodeName,airOutletNodeName);
      }
    } else {
      if( _supplementalHeatingCoil->iddObject().type() == IddObjectType::Coil_Heating_Fuel )
      {
        _supplementalHeatingCoil->setString(Coil_Heating_FuelFields::AirInletNodeName,fanOutletNodeName);

        _supplementalHeatingCoil->setString(Coil_Heating_FuelFields::AirOutletNodeName,airOutletNodeName);
      }
      else if( _supplementalHeatingCoil->iddObject().type() == IddObjectType::Coil_Heating_Electric )
      {
        _supplementalHeatingCoil->setString(Coil_Heating_ElectricFields::AirInletNodeName,fanOutletNodeName);

        _supplementalHeatingCoil->setString(Coil_Heating_ElectricFields::AirOutletNodeName,airOutletNodeName);
      }
      else if( _supplementalHeatingCoil->iddObject().type() == IddObjectType::Coil_Heating_Water )
      {
        _supplementalHeatingCoil->setString(Coil_Heating_WaterFields::AirInletNodeName,fanOutletNodeName);

        _supplementalHeatingCoil->setString(Coil_Heating_WaterFields::AirOutletNodeName,airOutletNodeName);
      }
    }
  }

  // MaximumSupplyAirTemperaturefromSupplementalHeater
  if( modelObject.isMaximumSupplyAirTemperaturefromSupplementalHeaterAutosized() )
  {
    idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater,"Autosize");
  }
  else if( (value = modelObject.maximumSupplyAirTemperaturefromSupplementalHeater()) )
  {
    idfObject.setDouble(ZoneHVAC_WaterToAirHeatPumpFields::MaximumSupplyAirTemperaturefromSupplementalHeater,value.get());
  }

  // MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation
  if( (value = modelObject.maximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation()) )
  {
    idfObject.setDouble(ZoneHVAC_WaterToAirHeatPumpFields::MaximumOutdoorDryBulbTemperatureforSupplementalHeaterOperation,value.get());
  }

  //Outdoor Dry-bulb Temperature Sensor Node Name
  idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::OutdoorDryBulbTemperatureSensorNodeName,"");

  // FanPlacement
  idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::FanPlacement,modelObject.fanPlacement());

  // SupplyAirFanOperatingModeScheduleName
  if( boost::optional<Schedule> schedule = modelObject.supplyAirFanOperatingModeSchedule() )
  {
    if( boost::optional<IdfObject> _schedule = translateAndMapModelObject(schedule.get()) )
    {
      idfObject.setString(ZoneHVAC_WaterToAirHeatPumpFields::SupplyAirFanOperatingModeScheduleName,_schedule->name().get());
    }
  }

  return idfObject;
}

} // energyplus

} // openstudio

