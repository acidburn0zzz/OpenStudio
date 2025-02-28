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

#ifndef MODEL_STRAIGHTCOMPONENT_HPP
#define MODEL_STRAIGHTCOMPONENT_HPP

#include "ModelAPI.hpp"
#include "HVACComponent.hpp"
#include "Connection.hpp"

namespace openstudio {
namespace model {

class AirLoopHVAC;
class AirflowNetworkEquivalentDuct;

namespace detail{
  class StraightComponent_Impl;
}

/** StraightComponent is the base class for HVACComponent objects which have precisely one inlet port and one outlet port.
 *
 *  A StraighComponent may appear on either an AirLoopHVAC or a PlantLoop.
 */
class MODEL_API StraightComponent : public HVACComponent {

  public:

  StraightComponent(IddObjectType type,const Model& model);

  virtual ~StraightComponent() {}

  std::vector<openstudio::IdfObject> remove();

  bool removeFromLoop();

  /** Returns the inlet port. **/
   unsigned inletPort();

  /** Returns the outlet port. **/
   unsigned outletPort();

  /** Returns the optional ModelObject connected to the inlet port. **/
   boost::optional<ModelObject> inletModelObject();

  /** Returns the optional ModelObject connected to the outlet port. **/
   boost::optional<ModelObject> outletModelObject();

  /** Returns the optional AirLoopHVAC object that this AirToAirComponent is attached to.
   *
   *  Reimplemented from HVACComponent.
   */
  boost::optional<AirLoopHVAC> airLoopHVAC() const;

  bool addToNode(Node & node);

  ModelObject clone(Model model) const;

  void disconnect();

  protected:

  friend class Model;

  friend class openstudio::IdfObject;

  /// @cond

  typedef detail::StraightComponent_Impl ImplType;

  explicit StraightComponent(std::shared_ptr<detail::StraightComponent_Impl> impl);

  private:

  REGISTER_LOGGER("openstudio.model.StraightComponent");

  /// @endcond

};

typedef boost::optional<StraightComponent> OptionalStraightComponent;

typedef std::vector<StraightComponent> StraightComponentVector;

} // model
} // openstudio

#endif // MODEL_STRAIGHTCOMPONENT_HPP

