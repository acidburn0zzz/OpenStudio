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

#ifndef MODEL_ZONEHVACPACKAGEDTERMINALAIRCONDITIONER_HPP
#define MODEL_ZONEHVACPACKAGEDTERMINALAIRCONDITIONER_HPP

#include "ModelAPI.hpp"
#include "ZoneHVACComponent.hpp"

namespace openstudio {
namespace model {

class Schedule;
class HVACComponent;

namespace detail {

  class ZoneHVACPackagedTerminalAirConditioner_Impl;

} // detail

/** ZoneHVACPackagedTerminalAirConditioner is a ZoneHVACComponent that wraps the
 *  OpenStudio IDD object 'OS:ZoneHVAC:PackagedTerminalAirConditioner'. */
class MODEL_API ZoneHVACPackagedTerminalAirConditioner : public ZoneHVACComponent
{
  public:
  /** @name Constructors and Destructors */
  //@{

  ZoneHVACPackagedTerminalAirConditioner( const Model& model,
                                          Schedule & availabilitySchedule,
                                          HVACComponent & supplyAirFan,
                                          HVACComponent & heatingCoil,
                                          HVACComponent & coolingCoil );

  virtual ~ZoneHVACPackagedTerminalAirConditioner() {}

  //@}

  static IddObjectType iddObjectType();


  static std::vector<std::string> outdoorAirMixerObjectTypeValues();

  /** \deprecated */
  static std::vector<std::string> validOutdoorAirMixerObjectTypeValues();

  static std::vector<std::string> fanPlacementValues();

  /** \deprecated */
  static std::vector<std::string> validFanPlacementValues();

  /** @name Getters */
  //@{

  Schedule availabilitySchedule() const;

  std::string outdoorAirMixerObjectType() const;

  std::string outdoorAirMixerName() const;

  /** In EnergyPlus 8.3.0 and above this property maps to the EnergyPlus field "Cooling Supply Air Flow Rate" **/
  boost::optional<double> supplyAirFlowRateDuringCoolingOperation() const;

  bool isSupplyAirFlowRateDuringCoolingOperationAutosized() const;

  /** In EnergyPlus 8.3.0 and above this property maps to the EnergyPlus field "Heating Supply Air Flow Rate" **/
  boost::optional<double> supplyAirFlowRateDuringHeatingOperation() const;

  bool isSupplyAirFlowRateDuringHeatingOperationAutosized() const;

  /** In EnergyPlus 8.3.0 and above this property maps to the EnergyPlus field "No Load Supply Air Flow Rate" **/
  boost::optional<double> supplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const;

  bool isSupplyAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;

  /** In EnergyPlus 8.3.0 and above this property maps to the EnergyPlus field "Cooling Outdoor Air Flow Rate" **/
  boost::optional<double> outdoorAirFlowRateDuringCoolingOperation() const;

  bool isOutdoorAirFlowRateDuringCoolingOperationAutosized() const;

  /** In EnergyPlus 8.3.0 and above this property maps to the EnergyPlus field "Heating Outdoor Air Flow Rate" **/
  boost::optional<double> outdoorAirFlowRateDuringHeatingOperation() const;

  bool isOutdoorAirFlowRateDuringHeatingOperationAutosized() const;

  /** In EnergyPlus 8.3.0 and above this property maps to the EnergyPlus field "No Load Outdoor Air Flow Rate" **/
  boost::optional<double> outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const;

  bool isOutdoorAirFlowRateWhenNoCoolingorHeatingisNeededAutosized() const;

  HVACComponent supplyAirFan() const;

  HVACComponent heatingCoil() const;

  HVACComponent coolingCoil() const;

  std::string fanPlacement() const;

  bool isFanPlacementDefaulted() const;

  boost::optional<Schedule> supplyAirFanOperatingModeSchedule() const;

  //@}
  /** @name Setters */
  //@{

  bool setAvailabilitySchedule(Schedule& schedule );

  bool setOutdoorAirMixerObjectType(std::string outdoorAirMixerObjectType);

  bool setOutdoorAirMixerName(std::string outdoorAirMixerName);

  bool setSupplyAirFlowRateDuringCoolingOperation(double supplyAirFlowRateDuringCoolingOperation);

  void autosizeSupplyAirFlowRateDuringCoolingOperation();

  bool setSupplyAirFlowRateDuringHeatingOperation(double supplyAirFlowRateDuringHeatingOperation);

  void autosizeSupplyAirFlowRateDuringHeatingOperation();

  bool setSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded(double supplyAirFlowRateWhenNoCoolingorHeatingisNeeded);

  void resetSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();

  void autosizeSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded();

  bool setOutdoorAirFlowRateDuringCoolingOperation(double outdoorAirFlowRateDuringCoolingOperation);

  void autosizeOutdoorAirFlowRateDuringCoolingOperation();

  bool setOutdoorAirFlowRateDuringHeatingOperation(double outdoorAirFlowRateDuringHeatingOperation);

  void autosizeOutdoorAirFlowRateDuringHeatingOperation();

  bool setOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded(double outdoorAirFlowRateWhenNoCoolingorHeatingisNeeded);

  void resetOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();

  void autosizeOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded();

  bool setSupplyAirFan( HVACComponent & fan );

  bool setHeatingCoil( HVACComponent & heatingCoil );

  bool setCoolingCoil( HVACComponent & coolingCoil );

  bool setFanPlacement(std::string fanPlacement);

  void resetFanPlacement();

  /** Sets the supply air fan operating mode schedule. Values of zero indicate that the fan
   *  cycles on and off with the active (heating or cooling) coil. Other values operate the
   *  fan continuously. */
  bool setSupplyAirFanOperatingModeSchedule(Schedule& schedule);

  void resetSupplyAirFanOperatingModeSchedule();

  //@}
  /** @name Other */
  //@{

  boost::optional<double> autosizedSupplyAirFlowRateDuringCoolingOperation() const ;

  boost::optional<double> autosizedSupplyAirFlowRateDuringHeatingOperation() const ;

  boost::optional<double> autosizedSupplyAirFlowRateWhenNoCoolingorHeatingisNeeded() const ;

  boost::optional<double> autosizedOutdoorAirFlowRateDuringCoolingOperation() const ;

  boost::optional<double> autosizedOutdoorAirFlowRateDuringHeatingOperation() const ;

  boost::optional<double> autosizedOutdoorAirFlowRateWhenNoCoolingorHeatingisNeeded() const ;



  //@}
 protected:
  /// @cond
  typedef detail::ZoneHVACPackagedTerminalAirConditioner_Impl ImplType;

  explicit ZoneHVACPackagedTerminalAirConditioner(std::shared_ptr<detail::ZoneHVACPackagedTerminalAirConditioner_Impl> impl);

  friend class detail::ZoneHVACPackagedTerminalAirConditioner_Impl;
  friend class Model;
  friend class IdfObject;
  friend class openstudio::detail::IdfObject_Impl;

  /// @endcond
 private:

  REGISTER_LOGGER("openstudio.model.ZoneHVACPackagedTerminalAirConditioner");
};

/** \relates ZoneHVACPackagedTerminalAirConditioner*/
typedef boost::optional<ZoneHVACPackagedTerminalAirConditioner> OptionalZoneHVACPackagedTerminalAirConditioner;

/** \relates ZoneHVACPackagedTerminalAirConditioner*/
typedef std::vector<ZoneHVACPackagedTerminalAirConditioner> ZoneHVACPackagedTerminalAirConditionerVector;

} // model
} // openstudio

#endif // MODEL_ZONEHVACPACKAGEDTERMINALAIRCONDITIONER_HPP
