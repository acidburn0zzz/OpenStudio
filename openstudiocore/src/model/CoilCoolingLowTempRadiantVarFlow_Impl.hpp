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

#ifndef MODEL_COILCOOLINGLOWTEMPRADIANTVARFLOW_IMPL_HPP
#define MODEL_COILCOOLINGLOWTEMPRADIANTVARFLOW_IMPL_HPP

#include "ModelAPI.hpp"
#include "StraightComponent_Impl.hpp"

namespace openstudio {
namespace model {

class Schedule;

namespace detail {

/** CoilCoolingLowTempRadiantVarFlow_Impl is a StraightComponent_Impl that is the implementation class for CoilCoolingLowTempRadiantVarFlow.*/
class MODEL_API CoilCoolingLowTempRadiantVarFlow_Impl : public StraightComponent_Impl {

   public:
    /** @name Constructors and Destructors */
    //@{

    CoilCoolingLowTempRadiantVarFlow_Impl(const IdfObject& idfObject,
                                          Model_Impl* model,
                                          bool keepHandle);

    CoilCoolingLowTempRadiantVarFlow_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                          Model_Impl* model,
                                          bool keepHandle);

    CoilCoolingLowTempRadiantVarFlow_Impl(const CoilCoolingLowTempRadiantVarFlow_Impl& other,
                                          Model_Impl* model,
                                          bool keepHandle);

    virtual ~CoilCoolingLowTempRadiantVarFlow_Impl() {}

    //@}
    /** @name Virtual Methods */
    //@{

    virtual const std::vector<std::string>& outputVariableNames() const override;

    virtual IddObjectType iddObjectType() const override;

    virtual std::vector<ScheduleTypeKey> getScheduleTypeKeys(const Schedule& schedule) const override;

    virtual unsigned inletPort() override;

    virtual unsigned outletPort() override;

    virtual boost::optional<ZoneHVACComponent> containingZoneHVACComponent() const override;

    //@}
    /** @name Getters */
    //@{

    boost::optional<double> maximumColdWaterFlow() const;

    bool isMaximumColdWaterFlowDefaulted() const;

    bool isMaximumColdWaterFlowAutosized() const;

    double coolingControlThrottlingRange() const;

    bool isCoolingControlThrottlingRangeDefaulted() const;

    boost::optional<Schedule> coolingControlTemperatureSchedule() const;

    std::string condensationControlType() const;

    bool isCondensationControlTypeDefaulted() const;

    double condensationControlDewpointOffset() const;

    bool isCondensationControlDewpointOffsetDefaulted() const;

  boost::optional<double> autosizedMaximumColdWaterFlow() const ;

  virtual void autosize() override;

  virtual void applySizingValues() override;

    //@}
    /** @name Setters */
    //@{

    bool setMaximumColdWaterFlow(boost::optional<double> maximumColdWaterFlow);

    void resetMaximumColdWaterFlow();

    void autosizeMaximumColdWaterFlow();

    bool setCoolingControlThrottlingRange(double coolingControlThrottlingRange);

    void resetCoolingControlThrottlingRange();

    bool setCoolingControlTemperatureSchedule(Schedule& schedule);

    void resetCoolingControlTemperatureSchedule();

    bool setCondensationControlType(std::string condensationControlType);

    void resetCondensationControlType();

    bool setCondensationControlDewpointOffset(double condensationControlDewpointOffset);

    void resetCondensationControlDewpointOffset();

    //@}
    /** @name Other */
    //@{

    bool addToNode(Node & node) override;

    // Used to find the ZoneHVAC that contains this coil
    boost::optional<ZoneHVACLowTempRadiantVarFlow> parentZoneHVAC() const;

    //@}
   protected:
   private:
    REGISTER_LOGGER("openstudio.model.CoilCoolingLowTempRadiantVarFlow");

    std::vector<std::string> condensationControlTypeValues() const;

    //boost::optional<ModelObject> coolingWaterInletNodeAsModelObject() const;
    //boost::optional<ModelObject> coolingWaterOutletNodeAsModelObject() const;
    boost::optional<ModelObject> coolingControlTemperatureScheduleAsModelObject() const;

    //bool setCoolingWaterInletNodeAsModelObject(const boost::optional<ModelObject>& modelObject);
    //bool setCoolingWaterOutletNodeAsModelObject(const boost::optional<ModelObject>& modelObject);
    bool setCoolingControlTemperatureScheduleAsModelObject(const boost::optional<ModelObject>& modelObject);
  };

} // detail

} // model
} // openstudio

#endif // MODEL_COILCOOLINGLOWTEMPRADIANTVARFLOW_IMPL_HPP
