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

#ifndef MODEL_RADIANCEPARAMETERS_IMPL_HPP
#define MODEL_RADIANCEPARAMETERS_IMPL_HPP

#include "ModelAPI.hpp"
#include "ModelObject_Impl.hpp"

#include "../utilities/units/Quantity.hpp"
#include "../utilities/units/OSOptionalQuantity.hpp"

namespace openstudio {
namespace model {

namespace detail {

  /** RadianceParameters_Impl is a ModelObject_Impl that is the implementation class for RadianceParameters.*/
  class MODEL_API RadianceParameters_Impl : public ModelObject_Impl {
























































    // TODO: Add relationships for objects related to this one, but not pointed to by the underlying data.
    //       Such relationships can be generated by the GenerateRelationships.rb script.
   public:
    /** @name Constructors and Destructors */
    //@{

    RadianceParameters_Impl(const IdfObject& idfObject,
                            Model_Impl* model,
                            bool keepHandle);

    RadianceParameters_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                            Model_Impl* model,
                            bool keepHandle);

    RadianceParameters_Impl(const RadianceParameters_Impl& other,
                            Model_Impl* model,
                            bool keepHandle);

    virtual ~RadianceParameters_Impl();

    //@}

    /** @name Virtual Methods */
    //@{

    virtual const std::vector<std::string>& outputVariableNames() const override;

    virtual IddObjectType iddObjectType() const override;

    //@}
    /** @name Getters */
    //@{

    int accumulatedRaysperRecord() const;

    bool isAccumulatedRaysperRecordDefaulted() const;

    double directThreshold() const;

    Quantity getDirectThreshold(bool returnIP=false) const;

    bool isDirectThresholdDefaulted() const;

    double directCertainty() const;

    Quantity getDirectCertainty(bool returnIP=false) const;

    bool isDirectCertaintyDefaulted() const;

    double directJitter() const;

    Quantity getDirectJitter(bool returnIP=false) const;

    bool isDirectJitterDefaulted() const;

    double directPretest() const;

    Quantity getDirectPretest(bool returnIP=false) const;

    bool isDirectPretestDefaulted() const;

    int ambientBouncesVMX() const;

    bool isAmbientBouncesVMXDefaulted() const;

    int ambientBouncesDMX() const;

    bool isAmbientBouncesDMXDefaulted() const;

    int ambientDivisionsVMX() const;

    bool isAmbientDivisionsVMXDefaulted() const;

    int ambientDivisionsDMX() const;

    bool isAmbientDivisionsDMXDefaulted() const;

    int ambientSupersamples() const;

    bool isAmbientSupersamplesDefaulted() const;

    double limitWeightVMX() const;

    Quantity getLimitWeightVMX(bool returnIP=false) const;

    bool isLimitWeightVMXDefaulted() const;

    double limitWeightDMX() const;

    Quantity getLimitWeightDMX(bool returnIP=false) const;

    bool isLimitWeightDMXDefaulted() const;

    int klemsSamplingDensity() const;

    bool isKlemsSamplingDensityDefaulted() const;

    std::string skyDiscretizationResolution() const;

    bool isCoarseSettings();

    bool isFineSettings();

    //@}
    /** @name Setters */
    //@{

    bool setAccumulatedRaysperRecord(int accumulatedRaysperRecord);

    void resetAccumulatedRaysperRecord();

    bool setDirectThreshold(double directThreshold);

    bool setDirectThreshold(const Quantity& directThreshold);

    void resetDirectThreshold();

    bool setDirectCertainty(double directCertainty);

    bool setDirectCertainty(const Quantity& directCertainty);

    void resetDirectCertainty();

    bool setDirectJitter(double directJitter);

    bool setDirectJitter(const Quantity& directJitter);

    void resetDirectJitter();

    bool setDirectPretest(double directPretest);

    bool setDirectPretest(const Quantity& directPretest);

    void resetDirectPretest();

    bool setAmbientBouncesVMX(int ambientBouncesVMX);

    void resetAmbientBouncesVMX();

    bool setAmbientBouncesDMX(int ambientBouncesDMX);

    void resetAmbientBouncesDMX();

    bool setAmbientDivisionsVMX(int ambientDivisionsVMX);

    void resetAmbientDivisionsVMX();

    bool setAmbientDivisionsDMX(int ambientDivisionsDMX);

    void resetAmbientDivisionsDMX();

    bool setAmbientSupersamples(int ambientSupersamples);

    void resetAmbientSupersamples();

    bool setLimitWeightVMX(double limitWeightVMX);

    bool setLimitWeightVMX(const Quantity& limitWeightVMX);

    void resetLimitWeightVMX();

    bool setLimitWeightDMX(double limitWeightDMX);

    bool setLimitWeightDMX(const Quantity& limitWeightDMX);

    void resetLimitWeightDMX();

    bool setKlemsSamplingDensity(int klemsSamplingDensity);

    void resetKlemsSamplingDensity();

    bool setSkyDiscretizationResolution(std::string skyDiscretizationResolution);

    void resetSkyDiscretizationResolution();

    void applyCoarseSettings();

    void applyFineSettings();

    //@}
    /** @name Other */
    //@{

    //@}
   protected:
   private:
    REGISTER_LOGGER("openstudio.model.RadianceParameters");

    openstudio::Quantity directThreshold_SI() const;
    openstudio::Quantity directThreshold_IP() const;
    openstudio::Quantity directCertainty_SI() const;
    openstudio::Quantity directCertainty_IP() const;
    openstudio::Quantity directJitter_SI() const;
    openstudio::Quantity directJitter_IP() const;
    openstudio::Quantity directPretest_SI() const;
    openstudio::Quantity directPretest_IP() const;
    openstudio::Quantity limitWeightVMX_SI() const;
    openstudio::Quantity limitWeightVMX_IP() const;
    openstudio::Quantity limitWeightDMX_SI() const;
    openstudio::Quantity limitWeightDMX_IP() const;
    std::vector<std::string> skyDiscretizationResolutionValues() const;
 };

} // detail

} // model
} // openstudio

#endif // MODEL_RADIANCEPARAMETERS_IMPL_HPP
