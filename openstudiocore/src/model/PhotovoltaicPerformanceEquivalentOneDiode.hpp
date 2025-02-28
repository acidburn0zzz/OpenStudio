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

#ifndef MODEL_PHOTOVOLTAICPERFORMANCEEQUIVALENTONEDIODE_HPP
#define MODEL_PHOTOVOLTAICPERFORMANCEEQUIVALENTONEDIODE_HPP

#include "ModelAPI.hpp"
#include "PhotovoltaicPerformance.hpp"

namespace openstudio {

namespace model {

namespace detail {

  class PhotovoltaicPerformanceEquivalentOneDiode_Impl;

} // detail

/** PhotovoltaicPerformanceEquivalentOneDiode is a PhotovoltaicPerformance that wraps the OpenStudio IDD object 'OS:PhotovoltaicPerformance:EquivalentOne-Diode'. */
class MODEL_API PhotovoltaicPerformanceEquivalentOneDiode : public PhotovoltaicPerformance {
 public:
  /** @name Constructors and Destructors */
  //@{

  explicit PhotovoltaicPerformanceEquivalentOneDiode(const Model& model);

  virtual ~PhotovoltaicPerformanceEquivalentOneDiode() {}

  //@}

  static IddObjectType iddObjectType();

  static std::vector<std::string> celltypeValues();

  /** @name Getters */
  //@{

  std::string celltype() const;

  bool isCelltypeDefaulted() const;


  int numberOfCellsInSeries() const;


  bool isNumberOfCellsInSeriesDefaulted() const;

  double activeArea() const;

  bool isActiveAreaDefaulted() const;

  double transmittanceAbsorptanceProduct() const;

  bool isTransmittanceAbsorptanceProductDefaulted() const;

  double semiconductorBandgap() const;

  bool isSemiconductorBandgapDefaulted() const;

  double shuntResistance() const;

  bool isShuntResistanceDefaulted() const;

  double shortCircuitCurrent() const;

  bool isShortCircuitCurrentDefaulted() const;

  double openCircuitVoltage() const;

  bool isOpenCircuitVoltageDefaulted() const;

  double referenceTemperature() const;

  bool isReferenceTemperatureDefaulted() const;

  double referenceInsolation() const;

  bool isReferenceInsolationDefaulted() const;

  double moduleCurrentatMaximumPower() const;

  bool isModuleCurrentatMaximumPowerDefaulted() const;

  double moduleVoltageatMaximumPower() const;

  bool isModuleVoltageatMaximumPowerDefaulted() const;

  double temperatureCoefficientofShortCircuitCurrent() const;

  bool isTemperatureCoefficientofShortCircuitCurrentDefaulted() const;

  double temperatureCoefficientofOpenCircuitVoltage() const;

  bool isTemperatureCoefficientofOpenCircuitVoltageDefaulted() const;

  double nominalOperatingCellTemperatureTestAmbientTemperature() const;

  bool isNominalOperatingCellTemperatureTestAmbientTemperatureDefaulted() const;

  double nominalOperatingCellTemperatureTestCellTemperature() const;

  bool isNominalOperatingCellTemperatureTestCellTemperatureDefaulted() const;

  double nominalOperatingCellTemperatureTestInsolation() const;

  bool isNominalOperatingCellTemperatureTestInsolationDefaulted() const;

  double moduleHeatLossCoefficient() const;

  bool isModuleHeatLossCoefficientDefaulted() const;

  double totalHeatCapacity() const;

  bool isTotalHeatCapacityDefaulted() const;

  //@}
  /** @name Setters */
  //@{

  bool setCelltype(std::string celltype);

  void resetCelltype();


  bool setNumberofCellsinSeries(int numberOfCellsInSeries);


  void resetNumberofCellsinSeries();

  bool setActiveArea(double activeArea);

  void resetActiveArea();

  bool setTransmittanceAbsorptanceProduct(double transmittanceAbsorptanceProduct);

  void resetTransmittanceAbsorptanceProduct();

  bool setSemiconductorBandgap(double semiconductorBandgap);

  void resetSemiconductorBandgap();

  bool setShuntResistance(double shuntResistance);

  void resetShuntResistance();

  bool setShortCircuitCurrent(double shortCircuitCurrent);

  void resetShortCircuitCurrent();

  bool setOpenCircuitVoltage(double openCircuitVoltage);

  void resetOpenCircuitVoltage();

  bool setReferenceTemperature(double referenceTemperature);

  void resetReferenceTemperature();

  bool setReferenceInsolation(double referenceInsolation);

  void resetReferenceInsolation();

  bool setModuleCurrentatMaximumPower(double moduleCurrentatMaximumPower);

  void resetModuleCurrentatMaximumPower();

  bool setModuleVoltageatMaximumPower(double moduleVoltageatMaximumPower);

  void resetModuleVoltageatMaximumPower();

  bool setTemperatureCoefficientofShortCircuitCurrent(double temperatureCoefficientofShortCircuitCurrent);

  void resetTemperatureCoefficientofShortCircuitCurrent();

  bool setTemperatureCoefficientofOpenCircuitVoltage(double temperatureCoefficientofOpenCircuitVoltage);

  void resetTemperatureCoefficientofOpenCircuitVoltage();

  bool setNominalOperatingCellTemperatureTestAmbientTemperature(double nominalOperatingCellTemperatureTestAmbientTemperature);

  void resetNominalOperatingCellTemperatureTestAmbientTemperature();

  bool setNominalOperatingCellTemperatureTestCellTemperature(double nominalOperatingCellTemperatureTestCellTemperature);

  void resetNominalOperatingCellTemperatureTestCellTemperature();

  bool setNominalOperatingCellTemperatureTestInsolation(double nominalOperatingCellTemperatureTestInsolation);

  void resetNominalOperatingCellTemperatureTestInsolation();

  bool setModuleHeatLossCoefficient(double moduleHeatLossCoefficient);

  void resetModuleHeatLossCoefficient();

  bool setTotalHeatCapacity(double totalHeatCapacity);

  void resetTotalHeatCapacity();

  //@}
  /** @name Other */
  //@{

  //@}
 protected:
  /// @cond
  typedef detail::PhotovoltaicPerformanceEquivalentOneDiode_Impl ImplType;

  explicit PhotovoltaicPerformanceEquivalentOneDiode(std::shared_ptr<detail::PhotovoltaicPerformanceEquivalentOneDiode_Impl> impl);

  friend class detail::PhotovoltaicPerformanceEquivalentOneDiode_Impl;
  friend class Model;
  friend class IdfObject;
  friend class openstudio::detail::IdfObject_Impl;
  /// @endcond
 private:
  REGISTER_LOGGER("openstudio.model.PhotovoltaicPerformanceEquivalentOneDiode");
};

/** \relates PhotovoltaicPerformanceEquivalentOneDiode*/
typedef boost::optional<PhotovoltaicPerformanceEquivalentOneDiode> OptionalPhotovoltaicPerformanceEquivalentOneDiode;

/** \relates PhotovoltaicPerformanceEquivalentOneDiode*/
typedef std::vector<PhotovoltaicPerformanceEquivalentOneDiode> PhotovoltaicPerformanceEquivalentOneDiodeVector;

} // model
} // openstudio

#endif // MODEL_PHOTOVOLTAICPERFORMANCEEQUIVALENTONEDIODE_HPP
