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

#ifndef OPENSTUDIO_INSPECTORCONTROLLER_HPP
#define OPENSTUDIO_INSPECTORCONTROLLER_HPP

#include "../model/Model.hpp"
#include "../model/ModelObject.hpp"

#include <boost/smart_ptr.hpp>

#include <QObject>

namespace openstudio {

class OSItem;

namespace model {

class ThermalZone;

class Loop;

class WaterToAirComponent;

class HVACComponent;

}

class InspectorView;

class InspectorController : public QObject
{
  Q_OBJECT

  public:

  InspectorController();

  virtual ~InspectorController();

  InspectorView * inspectorView();

  signals:

  void toggleUnitsClicked(bool displayIP);

  void itemRemoveClicked(OSItem *);

  void removeButtonClicked(bool);

  void workspaceObjectRemoved();

  public slots:

  void layoutModelObject( model::OptionalModelObject &, bool readOnly );

  void addBranchForZone(model::ThermalZone &);
  void removeBranchForZone(model::ThermalZone &);
  void moveBranchForZoneSupply(model::ThermalZone & zone, const Handle & newPlenumHandle);
  void moveBranchForZoneReturn(model::ThermalZone & zone, const Handle & newPlenumHandle);

  void addToLoop(model::Loop &, boost::optional<model::HVACComponent> &);
  void removeFromLoop(model::Loop &, boost::optional<model::HVACComponent> &);

  void toggleUnits(bool displayIP);

  private slots:

  void onViewDestroyed(QObject * object = nullptr);

  private:

  InspectorView * m_inspectorView;

  boost::optional<model::ModelObject> m_modelObject;
};

} // openstudio

#endif // OPENSTUDIO_INSPECTORCONTROLLER_HPP

