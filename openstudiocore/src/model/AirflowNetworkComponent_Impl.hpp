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

#ifndef MODEL_AIRFLOWNETWORKCOMPONENT_IMPL_HPP
#define MODEL_AIRFLOWNETWORKCOMPONENT_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace model {

namespace detail {

  class MODEL_API AirflowNetworkComponent_Impl : public ModelObject_Impl {
   public:
    /** @name Constructors and Destructors */
    //@{

    AirflowNetworkComponent_Impl(IddObjectType type, Model_Impl* model);

    AirflowNetworkComponent_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

    AirflowNetworkComponent_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                           Model_Impl* model,
                           bool keepHandle);

    AirflowNetworkComponent_Impl(const AirflowNetworkComponent_Impl& other, Model_Impl* model, bool keepHandles);

    virtual ~AirflowNetworkComponent_Impl() {}

    //@}
    /** @name Virtual Methods */
    //@{

    //virtual ModelObject clone(Model model) const override;

    //virtual boost::optional<ParentObject> parent() const override;

    //virtual std::vector<ModelObject> children() const override;

    //virtual std::vector<HVACComponent> edges(const boost::optional<HVACComponent> & prev) override;

    //** Returns the optional ModelObject that this component represents. **/
    virtual boost::optional<ModelObject> componentModelObject() const;

    //@}
    /** @name Getters */
    //@{

    //virtual unsigned inletPort() = 0;

    //virtual unsigned outletPort() = 0;

    //virtual boost::optional<ModelObject> inletModelObject();

    //virtual boost::optional<ModelObject> outletModelObject();

    //virtual boost::optional<AirLoopHVAC> airLoopHVAC() const override;

    //@}
    /** @name Setters */
    //@{


    //@}
    /** @name Other */
    //@{
    //virtual bool addToNode(Node & node) override;

    //virtual std::vector<openstudio::IdfObject> remove() override;

    //bool removeFromLoop();

    //void disconnect() override;

    //@}
   private:

    REGISTER_LOGGER("openstudio.model.AirflowNetworkComponent");
  };

} // detail

} // model
} // openstudio

#endif // MODEL_AIRFLOWNETWORKCOMPONENT_IMPL_HPP
