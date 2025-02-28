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

#ifndef MODEL_SETPOINTMANAGERWARMEST_IMPL_HPP
#define MODEL_SETPOINTMANAGERWARMEST_IMPL_HPP

#include "ModelAPI.hpp"
#include "SetpointManager_Impl.hpp"

namespace openstudio {
namespace model {

class Node;

namespace detail {

/** SetpointManagerWarmest_Impl is a SetpointManager_Impl that is the implementation class for SetpointManagerWarmest.*/
class MODEL_API SetpointManagerWarmest_Impl : public SetpointManager_Impl {
 public:
  /** @name Constructors and Destructors */
  //@{

  SetpointManagerWarmest_Impl(const IdfObject& idfObject,
                              Model_Impl* model,
                              bool keepHandle);

  SetpointManagerWarmest_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                              Model_Impl* model,
                              bool keepHandle);

  SetpointManagerWarmest_Impl(const SetpointManagerWarmest_Impl& other,
                              Model_Impl* model,
                              bool keepHandle);

  virtual ~SetpointManagerWarmest_Impl() {}

  //@}
  /** @name Virtual Methods */
  //@{

  virtual const std::vector<std::string>& outputVariableNames() const override;

  virtual IddObjectType iddObjectType() const override;

  //@}
  /** @name Getters */
  //@{

  virtual std::string controlVariable() const override;

  double minimumSetpointTemperature() const;

  double maximumSetpointTemperature() const;

  std::string strategy() const;

  virtual boost::optional<Node> setpointNode() const override;

  //@}
  /** @name Setters */
  //@{

  virtual bool setControlVariable(const std::string& controlVariable) override;

  bool setMinimumSetpointTemperature(double minimumSetpointTemperature);

  bool setMaximumSetpointTemperature(double maximumSetpointTemperature);

  bool setStrategy(const std::string& strategy);

  //@}
  /** @name Other */
  //@{

  //@}
 protected:
 private:
  virtual bool setSetpointNode(const Node& node) override;

  virtual void resetSetpointNode() override;

  REGISTER_LOGGER("openstudio.model.SetpointManagerWarmest");
};

} // detail

} // model
} // openstudio

#endif // MODEL_SETPOINTMANAGERWARMEST_IMPL_HPP

