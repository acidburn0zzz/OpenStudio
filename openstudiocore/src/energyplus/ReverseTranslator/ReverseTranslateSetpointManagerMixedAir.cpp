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

#include "../ReverseTranslator.hpp"
#include "../../model/SetpointManagerMixedAir.hpp"
#include "../../model/SetpointManagerMixedAir_Impl.hpp"
#include "../../model/Node.hpp"
#include "../../model/Node_Impl.hpp"
#include <utilities/idd/SetpointManager_MixedAir_FieldEnums.hxx>
#include "../../utilities/idd/IddEnums.hpp"
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

OptionalModelObject ReverseTranslator::translateSetpointManagerMixedAir( const WorkspaceObject & workspaceObject )
{
  if( workspaceObject.iddObject().type() != IddObjectType::SetpointManager_MixedAir )
  {
     LOG(Error, "WorkspaceObject is not IddObjectType: SetpointManager_MixedAir");
     return boost::none;
  }

  bool nodeFound = false;

  if( boost::optional<std::string> setpointNodeName = workspaceObject.getString(SetpointManager_MixedAirFields::SetpointNodeorNodeListName) )
  {
    boost::optional<Node> setpointNode = m_model.getModelObjectByName<Node>(setpointNodeName.get());

    if( setpointNode ) { nodeFound = true; }
  }

  if( ! nodeFound )
  {
    LOG(Error, workspaceObject.briefDescription() << " is not attached to a node in the model");

    return boost::none;
  }

  SetpointManagerMixedAir mo(m_model);

  boost::optional<std::string> s = workspaceObject.getString(SetpointManager_MixedAirFields::Name);
  if( s )
  {
    mo.setName(s.get());
  }

  s = workspaceObject.getString(SetpointManager_MixedAirFields::ReferenceSetpointNodeName);
  if( s )
  {
    boost::optional<Node> node = m_model.getModelObjectByName<Node>(s.get());

    if( node )
    {
      mo.setReferenceSetpointNode(node.get());
    }
  }

  s = workspaceObject.getString(SetpointManager_MixedAirFields::FanInletNodeName);
  if( s )
  {
    boost::optional<Node> node = m_model.getModelObjectByName<Node>(s.get());

    if( node )
    {
      mo.setFanInletNode(node.get());
    }
  }

  s = workspaceObject.getString(SetpointManager_MixedAirFields::FanOutletNodeName);
  if( s )
  {
    boost::optional<Node> node = m_model.getModelObjectByName<Node>(s.get());

    if( node )
    {
      mo.setFanOutletNode(node.get());
    }
  }

  s = workspaceObject.getString(SetpointManager_MixedAirFields::SetpointNodeorNodeListName);
  if( s )
  {
    boost::optional<Node> node = m_model.getModelObjectByName<Node>(s.get());

    if( node )
    {
      mo.addToNode(node.get());
    }
  }

  if( mo.setpointNode() )
  {
    return mo;
  }
  else
  {
    return boost::none;
  }
}

} // energyplus

} // openstudio

