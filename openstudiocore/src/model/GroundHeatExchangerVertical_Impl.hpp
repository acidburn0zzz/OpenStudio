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

#ifndef MODEL_GROUNDHEATEXCHANGERVERTICAL_IMPL_HPP
#define MODEL_GROUNDHEATEXCHANGERVERTICAL_IMPL_HPP

#include "ModelAPI.hpp"
#include "StraightComponent_Impl.hpp"

namespace openstudio {
namespace model {
namespace detail {

  /** GroundHeatExchangerVertical_Impl is a StraightComponent_Impl that is the implementation class for GroundHeatExchangerVertical.*/
  class MODEL_API GroundHeatExchangerVertical_Impl : public StraightComponent_Impl {
   public:
    /** @name Constructors and Destructors */
    //@{

    GroundHeatExchangerVertical_Impl(const IdfObject& idfObject,
                                     Model_Impl* model,
                                     bool keepHandle);

    GroundHeatExchangerVertical_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                     Model_Impl* model,
                                     bool keepHandle);

    GroundHeatExchangerVertical_Impl(const GroundHeatExchangerVertical_Impl& other,
                                     Model_Impl* model,
                                     bool keepHandle);

    virtual ~GroundHeatExchangerVertical_Impl() {}

    //@}
    /** @name Virtual Methods */
    //@{

    virtual const std::vector<std::string>& outputVariableNames() const override;

    virtual IddObjectType iddObjectType() const override;

    virtual ModelObject clone(Model model) const override;

    virtual unsigned inletPort() override;

    virtual unsigned outletPort() override;

    bool addToNode(Node & node) override;

    bool addGFunction(double gFunctionLN, double gFunctionGValue);

    void removeGFunction(unsigned groupIndex);

    void removeAllGFunctions();

    std::vector< std::pair<double,double> > gFunctions();

    //@}
    /** @name Getters */
    //@{

    boost::optional<double> maximumFlowRate() const;

    boost::optional<int> numberofBoreHoles() const;

    boost::optional<double> boreHoleLength() const;

    boost::optional<double> boreHoleRadius() const;

    boost::optional<double> groundThermalConductivity() const;

    boost::optional<double> groundThermalHeatCapacity() const;

    boost::optional<double> groundTemperature() const;

    boost::optional<double> designFlowRate() const;

    boost::optional<double> groutThermalConductivity() const;

    boost::optional<double> pipeThermalConductivity() const;

    boost::optional<double> pipeOutDiameter() const;

    boost::optional<double> uTubeDistance() const;

    boost::optional<double> pipeThickness() const;

    boost::optional<double> maximumLengthofSimulation() const;

    double gFunctionReferenceRatio() const;

    bool isGFunctionReferenceRatioDefaulted() const;

    //@}
    /** @name Setters */
    //@{

    bool setMaximumFlowRate(boost::optional<double> maximumFlowRate);

    void resetMaximumFlowRate();

    bool setNumberofBoreHoles(boost::optional<int> numberofBoreHoles);

    void resetNumberofBoreHoles();

    bool setBoreHoleLength(boost::optional<double> boreHoleLength);

    void resetBoreHoleLength();

    bool setBoreHoleRadius(boost::optional<double> boreHoleRadius);

    void resetBoreHoleRadius();

    bool setGroundThermalConductivity(boost::optional<double> groundThermalConductivity);

    void resetGroundThermalConductivity();

    bool setGroundThermalHeatCapacity(boost::optional<double> groundThermalHeatCapacity);

    void resetGroundThermalHeatCapacity();

    bool setGroundTemperature(boost::optional<double> groundTemperature);

    void resetGroundTemperature();

    bool setDesignFlowRate(boost::optional<double> designFlowRate);

    void resetDesignFlowRate();

    bool setGroutThermalConductivity(boost::optional<double> groutThermalConductivity);

    void resetGroutThermalConductivity();

    bool setPipeThermalConductivity(boost::optional<double> pipeThermalConductivity);

    void resetPipeThermalConductivity();

    bool setPipeOutDiameter(boost::optional<double> pipeOutDiameter);

    void resetPipeOutDiameter();

    bool setUTubeDistance(boost::optional<double> uTubeDistance);

    void resetUTubeDistance();

    bool setPipeThickness(boost::optional<double> pipeThickness);

    void resetPipeThickness();

    bool setMaximumLengthofSimulation(boost::optional<double> maximumLengthofSimulation);

    void resetMaximumLengthofSimulation();

    bool setGFunctionReferenceRatio(double gFunctionReferenceRatio);

    void resetGFunctionReferenceRatio();

    //@}
    /** @name Other */
    //@{

    //@}
   protected:
   private:
    REGISTER_LOGGER("openstudio.model.GroundHeatExchangerVertical");

    // TODO: Check the return types of these methods.
    // Optional getters for use by methods like children() so can remove() if the constructor fails.
    // There are other ways for the public versions of these getters to fail--perhaps all required
    // objects should be returned as boost::optionals

  };

} // detail

} // model
} // openstudio

#endif // MODEL_GROUNDHEATEXCHANGERVERTICAL_IMPL_HPP

