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

#ifndef MODEL_ELECTRICLOADCENTERSTORAGESIMPLE_IMPL_HPP
#define MODEL_ELECTRICLOADCENTERSTORAGESIMPLE_IMPL_HPP

#include "ModelAPI.hpp"
#include "ElectricalStorage_Impl.hpp"

namespace openstudio {
namespace model {

class Schedule;
class ThermalZone;

namespace detail {

  /** ElectricLoadCenterStorageSimple_Impl is a ElectricalStorage_Impl that is the implementation class for ElectricLoadCenterStorageSimple.*/
  class MODEL_API ElectricLoadCenterStorageSimple_Impl : public ElectricalStorage_Impl {
   public:
    /** @name Constructors and Destructors */
    //@{

    ElectricLoadCenterStorageSimple_Impl(const IdfObject& idfObject,
                                         Model_Impl* model,
                                         bool keepHandle);

    ElectricLoadCenterStorageSimple_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                         Model_Impl* model,
                                         bool keepHandle);

    ElectricLoadCenterStorageSimple_Impl(const ElectricLoadCenterStorageSimple_Impl& other,
                                         Model_Impl* model,
                                         bool keepHandle);

    virtual ~ElectricLoadCenterStorageSimple_Impl() {}

    //@}
    /** @name Virtual Methods */
    //@{

    virtual const std::vector<std::string>& outputVariableNames() const override;

    virtual IddObjectType iddObjectType() const override;

    virtual std::vector<ScheduleTypeKey> getScheduleTypeKeys(const Schedule& schedule) const override;

    //@}
    /** @name Getters */
    //@{

    // Convenience method to return the electricalLoadCenter on which it's assigned (optional)
    // Included in Base Class
    // boost::optional<ElectricLoadCenterDistribution> electricLoadCenterDistribution() const;

    Schedule availabilitySchedule() const;
    bool isAvailabilityScheduleDefaulted() const;

    virtual boost::optional<ThermalZone> thermalZone() const override;

    double radiativeFractionforZoneHeatGains() const;
    bool isRadiativeFractionforZoneHeatGainsDefaulted() const;

    double nominalEnergeticEfficiencyforCharging() const;
    bool isNominalEnergeticEfficiencyforChargingDefaulted() const;

    // TODO: I've requested an .IDD change in EnergyPlus, to make this "Nominal Energetic Efficiency for Discharging"
    // TODO: https://github.com/NREL/EnergyPlus/issues/5730
    double nominalDischargingEnergeticEfficiency() const;
    bool isNominalDischargingEnergeticEfficiencyDefaulted() const;

    double maximumStorageCapacity() const;

    double maximumPowerforDischarging() const;

    double maximumPowerforCharging() const;

    double initialStateofCharge() const;
    bool isInitialStateofChargeDefaulted() const;

    virtual std::vector<EMSActuatorNames> emsActuatorNames() const override;

    virtual std::vector<std::string> emsInternalVariableNames() const override;

    //@}
    /** @name Setters */
    //@{

    bool setAvailabilitySchedule(Schedule& schedule);
    void resetAvailabilitySchedule();

    // Override ElectricalStorage (Base class) methods
    virtual bool setThermalZone(const ThermalZone& thermalZone) override;
    virtual void resetThermalZone() override;

    bool setRadiativeFractionforZoneHeatGains(double radiativeFractionforZoneHeatGains);
    void resetRadiativeFractionforZoneHeatGains();

    bool setNominalEnergeticEfficiencyforCharging(double nominalEnergeticEfficiencyforCharging);
    void resetNominalEnergeticEfficiencyforCharging();

    bool setNominalDischargingEnergeticEfficiency(double nominalDischargingEnergeticEfficiency);
    void resetNominalDischargingEnergeticEfficiency();

    bool setMaximumStorageCapacity(double maximumStorageCapacity);

    bool setMaximumPowerforDischarging(double maximumPowerforDischarging);

    bool setMaximumPowerforCharging(double maximumPowerforCharging);

    bool setInitialStateofCharge(double initialStateofCharge);
    void resetInitialStateofCharge();

    //@}
    /** @name Other */
    //@{

    // TODO: Remove if not used. Don't think I need to override any of these
    //ModelObject clone(Model model) const override;

    //std::vector<openstudio::IdfObject> remove() override;

    //std::vector<ModelObject> children() const override;

    //@}
   protected:
   private:
    REGISTER_LOGGER("openstudio.model.ElectricLoadCenterStorageSimple");
    boost::optional<Schedule> optionalAvailabilitySchedule() const;
  };

} // detail

} // model
} // openstudio

#endif // MODEL_ELECTRICLOADCENTERSTORAGESIMPLE_IMPL_HPP

