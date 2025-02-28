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
#include "../../model/HumidifierSteamElectric.hpp"
#include "../../model/Schedule.hpp"
#include <utilities/idd/Humidifier_Steam_Electric_FieldEnums.hxx>
#include "../../utilities/idd/IddEnums.hpp"
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

boost::optional<IdfObject> ForwardTranslator::translateHumidifierSteamElectric( HumidifierSteamElectric & modelObject )
{
  OptionalDouble d;
  OptionalModelObject temp;

  // Name
  IdfObject idfObject = createRegisterAndNameIdfObject(openstudio::IddObjectType::Humidifier_Steam_Electric, modelObject);

  // Availability Schedule Name
  if( (temp = modelObject.availabilitySchedule()) )
  {
    if( boost::optional<IdfObject> _schedule = translateAndMapModelObject(temp.get()) )
    {
      idfObject.setString(Humidifier_Steam_ElectricFields::AvailabilityScheduleName,_schedule->name().get());
    }
  }

  // Rated Capacity
  if( modelObject.isRatedCapacityAutosized() ) {
    idfObject.setString(Humidifier_Steam_ElectricFields::RatedCapacity,"Autosize");
  } if( (d = modelObject.ratedCapacity()) ) {
    idfObject.setDouble(Humidifier_Steam_ElectricFields::RatedCapacity,d.get());
  }

  // Rated Power
  if( (d = modelObject.ratedPower()) )
  {
    idfObject.setDouble(Humidifier_Steam_ElectricFields::RatedPower,d.get());
  }
  else if( modelObject.isRatedPowerAutosized() )
  {
    idfObject.setString(Humidifier_Steam_ElectricFields::RatedPower,"Autosize");
  }

  // Rated Fan Power
  if( (d = modelObject.ratedFanPower()) )
  {
    idfObject.setDouble(Humidifier_Steam_ElectricFields::RatedFanPower,d.get());
  }

  // Standby Power
  if( (d = modelObject.standbyPower()) )
  {
    idfObject.setDouble(Humidifier_Steam_ElectricFields::StandbyPower,d.get());
  }

  // Air Inlet Node Name
  temp = modelObject.inletModelObject();
  if(temp)
  {
    idfObject.setString(Humidifier_Steam_ElectricFields::AirInletNodeName,temp->name().get());
  }

  // Air Outlet Node Name
  temp = modelObject.outletModelObject();
  if(temp)
  {
    idfObject.setString(Humidifier_Steam_ElectricFields::AirOutletNodeName,temp->name().get());
  }

  // Water Storage Tank Name
  // not currently used

  return idfObject;
}

} // energyplus

} // openstudio
