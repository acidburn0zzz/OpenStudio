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

#ifndef MODEL_COILHEATINGWATERBASEBOARD_IMPL_HPP
#define MODEL_COILHEATINGWATERBASEBOARD_IMPL_HPP

#include "ModelAPI.hpp"
#include "StraightComponent_Impl.hpp"
#include "ZoneHVACComponent.hpp"
#include "ZoneHVACComponent_Impl.hpp"

#include "../utilities/units/Quantity.hpp"
#include "../utilities/units/OSOptionalQuantity.hpp"

namespace openstudio {
namespace model {

namespace detail {

  /** CoilHeatingWaterBaseboard_Impl is a StraightComponent_Impl that is the implementation class for CoilHeatingWaterBaseboard.*/
  class MODEL_API CoilHeatingWaterBaseboard_Impl : public StraightComponent_Impl {
   public:
    /** @name Constructors and Destructors */
    //@{

    CoilHeatingWaterBaseboard_Impl(const IdfObject& idfObject,
                                   Model_Impl* model,
                                   bool keepHandle);

    CoilHeatingWaterBaseboard_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                   Model_Impl* model,
                                   bool keepHandle);

    CoilHeatingWaterBaseboard_Impl(const CoilHeatingWaterBaseboard_Impl& other,
                                   Model_Impl* model,
                                   bool keepHandle);

    virtual ~CoilHeatingWaterBaseboard_Impl() {}

    //@}

    /** @name Virtual Methods */
    //@{

    virtual const std::vector<std::string>& outputVariableNames() const override;

    virtual IddObjectType iddObjectType() const override;

    unsigned inletPort() override;

    unsigned outletPort() override;

    virtual boost::optional<ZoneHVACComponent> containingZoneHVACComponent() const override;

    //@}
    /** @name Getters */
    //@{

    std::string heatingDesignCapacityMethod() const;

    boost::optional<double> heatingDesignCapacity() const;

    bool isHeatingDesignCapacityAutosized() const;

    double heatingDesignCapacityPerFloorArea() const;

    double fractionofAutosizedHeatingDesignCapacity() const;

    boost::optional<double> uFactorTimesAreaValue() const;

    bool isUFactorTimesAreaValueDefaulted() const;

    bool isUFactorTimesAreaValueAutosized() const;

    boost::optional<double> maximumWaterFlowRate() const;

    bool isMaximumWaterFlowRateDefaulted() const;

    bool isMaximumWaterFlowRateAutosized() const;

    double convergenceTolerance() const;

    bool isConvergenceToleranceDefaulted() const;

  boost::optional<double> autosizedHeatingDesignCapacity() const ;

  boost::optional<double> autosizedUFactorTimesAreaValue() const ;

  boost::optional<double> autosizedMaximumWaterFlowRate() const ;

  virtual void autosize() override;

  virtual void applySizingValues() override;

    //@}
    /** @name Setters */
    //@{
    bool setHeatingDesignCapacityMethod(std::string heatingDesignCapacityMethod);

    bool setHeatingDesignCapacity(boost::optional<double> heatingDesignCapacity);

    void autosizeHeatingDesignCapacity();

    bool setHeatingDesignCapacityPerFloorArea(double heatingDesignCapacityPerFloorArea);

    bool setFractionofAutosizedHeatingDesignCapacity(double fractionofAutosizedHeatingDesignCapacity);

    bool setUFactorTimesAreaValue(boost::optional<double> uFactorTimesAreaValue);

    void resetUFactorTimesAreaValue();

    void autosizeUFactorTimesAreaValue();

    bool setMaximumWaterFlowRate(boost::optional<double> maximumWaterFlowRate);

    void resetMaximumWaterFlowRate();

    void autosizeMaximumWaterFlowRate();

    bool setConvergenceTolerance(double convergenceTolerance);

    void resetConvergenceTolerance();

    //@}
    /** @name Other */
    //@{

    bool addToNode(Node & node) override;

    //@}
   protected:
   private:
    REGISTER_LOGGER("openstudio.model.CoilHeatingWaterBaseboard");

  };

} // detail

} // model
} // openstudio

#endif // MODEL_COILHEATINGWATERBASEBOARD_IMPL_HPP
