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

#ifndef MODEL_OUTSIDESURFACECONVECTIONALGORITHM_IMPL_HPP
#define MODEL_OUTSIDESURFACECONVECTIONALGORITHM_IMPL_HPP

#include "ModelObject_Impl.hpp"

namespace openstudio {
namespace model {

namespace detail {

  class MODEL_API OutsideSurfaceConvectionAlgorithm_Impl : public ModelObject_Impl {



   public:
    /** @name Constructors and Destructors */
    //@{

    // constructor
    OutsideSurfaceConvectionAlgorithm_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

    // construct from workspace
    OutsideSurfaceConvectionAlgorithm_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                           Model_Impl* model,
                                           bool keepHandle);

    // clone copy constructor
    OutsideSurfaceConvectionAlgorithm_Impl(const OutsideSurfaceConvectionAlgorithm_Impl& other, Model_Impl* model, bool keepHandle);

    // virtual destructor
    virtual ~OutsideSurfaceConvectionAlgorithm_Impl() {}

    //@}
    /** @name Virtual Methods */
    //@{

    // return the parent object in the hierarchy
    virtual boost::optional<ParentObject> parent() const override;

    // set the parent, child may have to call methods on the parent
    virtual bool setParent(ParentObject& newParent) override;

    // Get all output variable names that could be associated with this object.
    virtual const std::vector<std::string>& outputVariableNames() const override;

    virtual IddObjectType iddObjectType() const override;

    //@}
    /** @name Getters */
    //@{

    std::string algorithm() const;

    bool isAlgorithmDefaulted() const;

    //@}
    /** @name Setters */
    //@{

    bool setAlgorithm(std::string algorithm);

    void resetAlgorithm();

    //@}

   private:

    REGISTER_LOGGER("openstudio.model.OutsideSurfaceConvectionAlgorithm");
  };

} // detail

} // model
} // openstudio

#endif // MODEL_OUTSIDESURFACECONVECTIONALGORITHM_IMPL_HPP
