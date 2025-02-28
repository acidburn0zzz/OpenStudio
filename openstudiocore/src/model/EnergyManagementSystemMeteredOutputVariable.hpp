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

#ifndef MODEL_ENERGYMANAGEMENTSYSTEMMETEREDOUTPUTVARIABLE_HPP
#define MODEL_ENERGYMANAGEMENTSYSTEMMETEREDOUTPUTVARIABLE_HPP

#include "ModelAPI.hpp"
#include "ModelObject.hpp"
#include "EnergyManagementSystemProgram.hpp"
#include "EnergyManagementSystemSubroutine.hpp"
#include "EnergyManagementSystemActuator.hpp"
#include "EnergyManagementSystemSensor.hpp"
#include "EnergyManagementSystemGlobalVariable.hpp"
#include "EnergyManagementSystemTrendVariable.hpp"
#include "EnergyManagementSystemInternalVariable.hpp"
#include "EnergyManagementSystemCurveOrTableIndexVariable.hpp"
#include "EnergyManagementSystemConstructionIndexVariable.hpp"

namespace openstudio {

namespace energyplus {
  class ReverseTranslator;
}

namespace model {

namespace detail {

  class EnergyManagementSystemMeteredOutputVariable_Impl;

} // detail

/** EnergyManagementSystemMeteredOutputVariable is a ModelObject that wraps the OpenStudio IDD object 'OS:EnergyManagementSystem:MeteredOutputVariable'. */
class MODEL_API EnergyManagementSystemMeteredOutputVariable : public ModelObject {
 public:
  /** @name Constructors and Destructors */
  //@{

  explicit EnergyManagementSystemMeteredOutputVariable(const Model& model, const std::string eMSVariableName);

  explicit EnergyManagementSystemMeteredOutputVariable(const Model& model, const EnergyManagementSystemActuator& object);

  explicit EnergyManagementSystemMeteredOutputVariable(const Model& model, const EnergyManagementSystemSensor& object);

  explicit EnergyManagementSystemMeteredOutputVariable(const Model& model, const EnergyManagementSystemGlobalVariable& object);

  explicit EnergyManagementSystemMeteredOutputVariable(const Model& model, const EnergyManagementSystemTrendVariable& object);

  explicit EnergyManagementSystemMeteredOutputVariable(const Model& model, const EnergyManagementSystemInternalVariable& object);

  explicit EnergyManagementSystemMeteredOutputVariable(const Model& model, const EnergyManagementSystemCurveOrTableIndexVariable& object);

  explicit EnergyManagementSystemMeteredOutputVariable(const Model& model, const EnergyManagementSystemConstructionIndexVariable& object);

  virtual ~EnergyManagementSystemMeteredOutputVariable() {}

  //@}

  static IddObjectType iddObjectType();

  static std::vector<std::string> updateFrequencyValues();

  static std::vector<std::string> resourceTypeValues();

  static std::vector<std::string> groupTypeValues();

  static std::vector<std::string> endUseCategoryValues();

  /** @name Getters */
  //@{

  std::string emsVariableName() const;

  std::string updateFrequency() const;

  std::string emsProgramOrSubroutineName() const;

  boost::optional<EnergyManagementSystemProgram> emsProgram() const;

  boost::optional<EnergyManagementSystemSubroutine> emsSubroutine() const;

  std::string resourceType() const;

  std::string groupType() const;

  std::string endUseCategory() const;

  std::string endUseSubcategory() const;

  std::string units() const;

  boost::optional<ModelObject> emsVariableObject() const;

  boost::optional<EnergyManagementSystemActuator> emsActuator() const;
  boost::optional<EnergyManagementSystemSensor> emsSensor() const;
  boost::optional<EnergyManagementSystemGlobalVariable> emsGlobalVariable() const;
  boost::optional<EnergyManagementSystemTrendVariable> emsTrendVariable() const;
  boost::optional<EnergyManagementSystemInternalVariable> emsInternalVariable() const;
  boost::optional<EnergyManagementSystemCurveOrTableIndexVariable> emsCurveOrTableIndexVariable() const;
  boost::optional<EnergyManagementSystemConstructionIndexVariable> emsConstructionIndexVariable() const;

  //@}
  /** @name Setters */
  //@{

  bool setEMSVariableName(const std::string& eMSVariableName);

  bool setUpdateFrequency(const std::string& updateFrequency);

  bool setEMSProgramOrSubroutineName(const EnergyManagementSystemProgram& program);

  bool setEMSProgramOrSubroutineName(const EnergyManagementSystemSubroutine& subroutine);

  void resetEMSProgramOrSubroutineName();

  bool setResourceType(const std::string& resourceType);

  bool setGroupType(const std::string& groupType);

  bool setEndUseCategory(const std::string& endUseCategory);

  bool setEndUseSubcategory(const std::string& endUseSubcategory);

  void resetEndUseSubcategory();

  bool setUnits(const std::string& units);

  void resetUnits();

  bool setEMSVariableName(const EnergyManagementSystemActuator& object);
  bool setEMSVariableName(const EnergyManagementSystemSensor& object);
  bool setEMSVariableName(const EnergyManagementSystemGlobalVariable& object);
  bool setEMSVariableName(const EnergyManagementSystemTrendVariable& object);
  bool setEMSVariableName(const EnergyManagementSystemInternalVariable& object);
  bool setEMSVariableName(const EnergyManagementSystemCurveOrTableIndexVariable& object);
  bool setEMSVariableName(const EnergyManagementSystemConstructionIndexVariable& object);

  //@}
  /** @name Other */
  //@{

  //@}
 protected:
  /// @cond
  typedef detail::EnergyManagementSystemMeteredOutputVariable_Impl ImplType;

  explicit EnergyManagementSystemMeteredOutputVariable(std::shared_ptr<detail::EnergyManagementSystemMeteredOutputVariable_Impl> impl);

  friend class detail::EnergyManagementSystemMeteredOutputVariable_Impl;
  friend class Model;
  friend class IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  friend class energyplus::ReverseTranslator;
  /// @endcond
 private:
  REGISTER_LOGGER("openstudio.model.EnergyManagementSystemMeteredOutputVariable");
  explicit EnergyManagementSystemMeteredOutputVariable(const Model& model);
};

/** \relates EnergyManagementSystemMeteredOutputVariable*/
typedef boost::optional<EnergyManagementSystemMeteredOutputVariable> OptionalEnergyManagementSystemMeteredOutputVariable;

/** \relates EnergyManagementSystemMeteredOutputVariable*/
typedef std::vector<EnergyManagementSystemMeteredOutputVariable> EnergyManagementSystemMeteredOutputVariableVector;

} // model
} // openstudio

#endif // MODEL_ENERGYMANAGEMENTSYSTEMMETEREDOUTPUTVARIABLE_HPP

