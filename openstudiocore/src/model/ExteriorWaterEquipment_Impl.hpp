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

#ifndef MODEL_EXTERIORWATEREQUIPMENT_IMPL_HPP
#define MODEL_EXTERIORWATEREQUIPMENT_IMPL_HPP

#include "ModelAPI.hpp"
#include "ExteriorLoadInstance_Impl.hpp"

namespace openstudio {
namespace model {

class ExteriorWaterEquipmentDefinition;
class Schedule;
class Facility;

namespace detail {

  /** ExteriorWaterEquipment_Impl is a ExteriorLoadInstance_Impl that is the implementation class for ExteriorWaterEquipment.*/
  class MODEL_API ExteriorWaterEquipment_Impl : public ExteriorLoadInstance_Impl {

   public:
    /** @name Constructors and Destructors */
    //@{

    ExteriorWaterEquipment_Impl(const IdfObject& idfObject, Model_Impl* model, bool keepHandle);

    ExteriorWaterEquipment_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                        Model_Impl* model,
                        bool keepHandle);

    ExteriorWaterEquipment_Impl(const ExteriorWaterEquipment_Impl& other,
                        Model_Impl* model,
                        bool keepHandle);

    virtual ~ExteriorWaterEquipment_Impl() {}

    //@}
    /** @name Virtual Methods */
    //@{

    virtual boost::optional<ParentObject> parent() const override;

    virtual const std::vector<std::string>& outputVariableNames() const override;

    virtual IddObjectType iddObjectType() const override;

    virtual std::vector<ScheduleTypeKey> getScheduleTypeKeys(const Schedule& schedule) const override;

    virtual double multiplier() const override;

    virtual bool isMultiplierDefaulted() const override;

    virtual bool setDefinition(const ExteriorLoadDefinition& definition) override;

    //@}
    /** @name Getters */
    //@{

    ExteriorWaterEquipmentDefinition exteriorWaterEquipmentDefinition() const;

    Schedule schedule() const;

    std::string endUseSubcategory() const;

    bool isEndUseSubcategoryDefaulted() const;

    //@}
    /** @name Setters */
    //@{

    bool setExteriorWaterEquipmentDefinition(const ExteriorWaterEquipmentDefinition& exteriorWaterEquipmentDefinition);

    bool setSchedule(Schedule& schedule);

    void resetSchedule();

    bool setMultiplier(double multiplier);

    void resetMultiplier();

    bool setEndUseSubcategory(std::string endUseSubcategory);

    void resetEndUseSubcategory();

    //@}
    /** @name Other */
    //@{

    Facility facility() const;

    //@}
   protected:

    // index of the definition name
    virtual int definitionIndex() const override;

   private:
    REGISTER_LOGGER("openstudio.model.ExteriorWaterEquipment");

    boost::optional<ModelObject> exteriorWaterEquipmentDefinitionAsModelObject() const;
    boost::optional<ModelObject> scheduleAsModelObject() const;
    boost::optional<ModelObject> facilityAsModelObject() const;

    bool setExteriorWaterEquipmentDefinitionAsModelObject(const boost::optional<ModelObject>& modelObject);
    bool setScheduleAsModelObject(const boost::optional<ModelObject>& modelObject);
  };

} // detail

} // model
} // openstudio

#endif // MODEL_EXTERIORWATEREQUIPMENT_IMPL_HPP

