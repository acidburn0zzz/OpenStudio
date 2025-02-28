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
#include "../../model/OutputVariable.hpp"
#include "../../model/OutputVariable_Impl.hpp"
#include "../../model/OutputMeter.hpp"
#include "../../model/OutputMeter_Impl.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/Schedule_Impl.hpp"
#include "../../model/EnergyManagementSystemMeteredOutputVariable.hpp"
#include "../../model/EnergyManagementSystemMeteredOutputVariable_Impl.hpp"

#include <utilities/idd/EnergyManagementSystem_MeteredOutputVariable_FieldEnums.hxx>
#include "../../utilities/idd/IddEnums.hpp"
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

using namespace std;

namespace openstudio {

namespace energyplus {

boost::optional<IdfObject> ForwardTranslator::translateEnergyManagementSystemMeteredOutputVariable(EnergyManagementSystemMeteredOutputVariable & modelObject)
{
  boost::optional<std::string> s;

  IdfObject idfObject(openstudio::IddObjectType::EnergyManagementSystem_MeteredOutputVariable);
  m_idfObjects.push_back(idfObject);
  //Name
  s = modelObject.name();
  if (s) {
    idfObject.setName(*s);
  }

  idfObject.setString(EnergyManagementSystem_MeteredOutputVariableFields::EMSVariableName, modelObject.emsVariableName());

  idfObject.setString(EnergyManagementSystem_MeteredOutputVariableFields::UpdateFrequency, modelObject.updateFrequency());

  s = modelObject.emsProgramOrSubroutineName();
  if (s.is_initialized()) {
    idfObject.setString(EnergyManagementSystem_MeteredOutputVariableFields::EMSProgramorSubroutineName, s.get());
  }
  idfObject.setString(EnergyManagementSystem_MeteredOutputVariableFields::ResourceType, modelObject.resourceType());

  idfObject.setString(EnergyManagementSystem_MeteredOutputVariableFields::GroupType, modelObject.groupType());

  idfObject.setString(EnergyManagementSystem_MeteredOutputVariableFields::EndUseCategory, modelObject.endUseCategory());

  s = modelObject.endUseSubcategory();
  if (s.is_initialized()) {
    idfObject.setString(EnergyManagementSystem_MeteredOutputVariableFields::EndUseSubcategory, s.get());
  }

  s = modelObject.units();
  if (s.is_initialized()) {
    idfObject.setString(EnergyManagementSystem_MeteredOutputVariableFields::Units, s.get());
  }
  return idfObject;
}

} // energyplus

} // openstudio

