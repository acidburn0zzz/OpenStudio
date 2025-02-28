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

#include "SpaceLoadInstancesWidget.hpp"

#include "OSAppBase.hpp"

#include "IconLibrary.hpp"
#include "ModelObjectItem.hpp"
#include "OSDropZone.hpp"
#include "OSVectorController.hpp"

#include "../shared_gui_components/OSDoubleEdit.hpp"
#include "../shared_gui_components/OSIntegerEdit.hpp"
#include "../shared_gui_components/OSLineEdit.hpp"

#include "../model/Building.hpp"
#include "../model/BuildingStory.hpp"
#include "../model/BuildingStory_Impl.hpp"
#include "../model/Building_Impl.hpp"
#include "../model/DefaultScheduleSet.hpp"
#include "../model/DefaultScheduleSet_Impl.hpp"
#include "../model/ElectricEquipment.hpp"
#include "../model/ElectricEquipmentDefinition.hpp"
#include "../model/ElectricEquipmentDefinition_Impl.hpp"
#include "../model/ElectricEquipment_Impl.hpp"
#include "../model/GasEquipment.hpp"
#include "../model/GasEquipmentDefinition.hpp"
#include "../model/GasEquipmentDefinition_Impl.hpp"
#include "../model/GasEquipment_Impl.hpp"
#include "../model/HotWaterEquipment.hpp"
#include "../model/HotWaterEquipmentDefinition.hpp"
#include "../model/HotWaterEquipmentDefinition_Impl.hpp"
#include "../model/HotWaterEquipment_Impl.hpp"
#include "../model/InternalMass.hpp"
#include "../model/InternalMassDefinition.hpp"
#include "../model/InternalMassDefinition_Impl.hpp"
#include "../model/InternalMass_Impl.hpp"
#include "../model/Lights.hpp"
#include "../model/LightsDefinition.hpp"
#include "../model/LightsDefinition_Impl.hpp"
#include "../model/Lights_Impl.hpp"
#include "../model/Luminaire.hpp"
#include "../model/LuminaireDefinition.hpp"
#include "../model/LuminaireDefinition_Impl.hpp"
#include "../model/Luminaire_Impl.hpp"
#include "../model/Model.hpp"
#include "../model/Model_Impl.hpp"
#include "../model/OtherEquipment.hpp"
#include "../model/OtherEquipmentDefinition.hpp"
#include "../model/OtherEquipmentDefinition_Impl.hpp"
#include "../model/OtherEquipment_Impl.hpp"
#include "../model/People.hpp"
#include "../model/PeopleDefinition.hpp"
#include "../model/PeopleDefinition_Impl.hpp"
#include "../model/People_Impl.hpp"
#include "../model/Schedule.hpp"
#include "../model/Schedule_Impl.hpp"
#include "../model/Space.hpp"
#include "../model/SpaceLoadDefinition.hpp"
#include "../model/SpaceLoadDefinition_Impl.hpp"
#include "../model/SpaceLoadInstance.hpp"
#include "../model/SpaceLoadInstance_Impl.hpp"
#include "../model/SpaceType.hpp"
#include "../model/SpaceType_Impl.hpp"
#include "../model/Space_Impl.hpp"
#include "../model/SteamEquipment.hpp"
#include "../model/SteamEquipmentDefinition.hpp"
#include "../model/SteamEquipmentDefinition_Impl.hpp"
#include "../model/SteamEquipment_Impl.hpp"

#include "../utilities/core/Assert.hpp"
#include "../utilities/idd/OS_Building_FieldEnums.hxx"
#include "../utilities/idd/OS_People_FieldEnums.hxx"
#include "../utilities/idd/OS_SpaceType_FieldEnums.hxx"
#include "../utilities/idd/OS_Space_FieldEnums.hxx"

#include "../utilities/idd/IddEnums.hpp"
#include <utilities/idd/IddEnums.hxx>


#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QStackedWidget>
#include <QTimer>
#include <QVBoxLayout>

namespace openstudio {

// SpaceLoadInstanceDefinitionVectorController

void SpaceLoadInstanceDefinitionVectorController::onChangeRelationship(const model::ModelObject& modelObject, int index, Handle newHandle, Handle oldHandle)
{
  emit itemIds(makeVector());
}

std::vector<OSItemId> SpaceLoadInstanceDefinitionVectorController::makeVector()
{
  std::vector<OSItemId> result;
  if (m_modelObject){
    if (!m_modelObject->handle().isNull()){
      model::SpaceLoadInstance spaceLoadInstance = m_modelObject->cast<model::SpaceLoadInstance>();
      result.push_back(modelObjectToItemId(spaceLoadInstance.definition(), false));
    }
  }
  return result;
}

void SpaceLoadInstanceDefinitionVectorController::onReplaceItem(OSItem * currentItem, const OSItemId& replacementItemId)
{
  if (m_modelObject){
    model::SpaceLoadInstance spaceLoadInstance = m_modelObject->cast<model::SpaceLoadInstance>();
    boost::optional<model::ModelObject> modelObject = this->getModelObject(replacementItemId);
    if (modelObject){
      if (modelObject->optionalCast<model::SpaceLoadDefinition>()){
        if (this->fromComponentLibrary(replacementItemId)){
          modelObject = modelObject->clone(m_modelObject->model());
        }
        spaceLoadInstance.setDefinition(modelObject->cast<model::SpaceLoadDefinition>());
      }
    }
  }
}

/****************************************************************************************************************************
*                                        SpaceLoadInstanceScheduleVectorController                                          *
****************************************************************************************************************************/

void SpaceLoadInstanceScheduleVectorController::attach(const model::ModelObject& modelObject)
{
  ModelObjectVectorController::attach(modelObject);

  model::SpaceLoadInstance spaceLoadInstance = m_modelObject->cast<model::SpaceLoadInstance>();
  attachOtherModelObjects(spaceLoadInstance);
}

void SpaceLoadInstanceScheduleVectorController::attachOtherModelObjects(const model::SpaceLoadInstance& spaceLoadInstance)
{
  boost::optional<model::Space> space = spaceLoadInstance.space();
  if (space){
    attachOtherModelObjects(*space);
  }

  boost::optional<model::SpaceType> spaceType = spaceLoadInstance.spaceType();
  if (spaceType){
    attachOtherModelObjects(*spaceType);
  }

  model::Building building = spaceLoadInstance.model().getUniqueModelObject<model::Building>();
  attachOtherModelObjects(building);
}

void SpaceLoadInstanceScheduleVectorController::attachOtherModelObjects(const model::Space& space)
{
  attachOtherModelObject(space);

  boost::optional<model::SpaceType> spaceType = space.spaceType();
  if (spaceType){
    attachOtherModelObjects(*spaceType);
  }

  boost::optional<model::BuildingStory> buildingStory = space.buildingStory();
  if (buildingStory){
    attachOtherModelObjects(*buildingStory);
  }
}

void SpaceLoadInstanceScheduleVectorController::attachOtherModelObjects(const model::SpaceType& spaceType)
{
  attachOtherModelObject(spaceType);

  boost::optional<model::DefaultScheduleSet> defaultScheduleSet = spaceType.defaultScheduleSet();
  if (defaultScheduleSet){
    attachOtherModelObjects(*defaultScheduleSet);
  }
}

void SpaceLoadInstanceScheduleVectorController::attachOtherModelObjects(const model::BuildingStory& buildingStory)
{
  attachOtherModelObject(buildingStory);

  boost::optional<model::DefaultScheduleSet> defaultScheduleSet = buildingStory.defaultScheduleSet();
  if (defaultScheduleSet){
    attachOtherModelObjects(*defaultScheduleSet);
  }
}

void SpaceLoadInstanceScheduleVectorController::attachOtherModelObjects(const model::Building& building)
{
  attachOtherModelObject(building);

  boost::optional<model::SpaceType> spaceType = building.spaceType();
  if (spaceType){
    attachOtherModelObjects(*spaceType);
  }

  boost::optional<model::DefaultScheduleSet> defaultScheduleSet = building.defaultScheduleSet();
  if (defaultScheduleSet){
    attachOtherModelObjects(*defaultScheduleSet);
  }
}

void SpaceLoadInstanceScheduleVectorController::attachOtherModelObjects(const model::DefaultScheduleSet& defaultScheduleSet)
{
  attachOtherModelObject(defaultScheduleSet);
}

void SpaceLoadInstanceScheduleVectorController::onChangeRelationship(const model::ModelObject& modelObject, int index, Handle newHandle, Handle oldHandle)
{
  model::SpaceLoadInstance spaceLoadInstance = m_modelObject->cast<model::SpaceLoadInstance>();

  if (modelObject.optionalCast<model::SpaceLoadInstance>()){
    detachOtherModelObjects();
    attachOtherModelObjects(spaceLoadInstance);
    emit itemIds(makeVector());
  }else if (modelObject.optionalCast<model::Space>()){
    if (index == OS_SpaceFields::SpaceTypeName){
      detachOtherModelObjects();
      attachOtherModelObjects(spaceLoadInstance);
      emit itemIds(makeVector());
    }else if (index == OS_SpaceFields::BuildingStoryName){
      detachOtherModelObjects();
      attachOtherModelObjects(spaceLoadInstance);
      emit itemIds(makeVector());
    }else if (index == OS_SpaceFields::DefaultScheduleSetName){
      detachOtherModelObjects();
      attachOtherModelObjects(spaceLoadInstance);
      emit itemIds(makeVector());
    }
  }else if (modelObject.optionalCast<model::SpaceType>()){
    if (index == OS_SpaceTypeFields::DefaultScheduleSetName){
      detachOtherModelObjects();
      attachOtherModelObjects(spaceLoadInstance);
      emit itemIds(makeVector());
    }
  }else if (modelObject.optionalCast<model::BuildingStory>()){
    if (index == OS_SpaceTypeFields::DefaultScheduleSetName){
      detachOtherModelObjects();
      attachOtherModelObjects(spaceLoadInstance);
      emit itemIds(makeVector());
    }
  }else if (modelObject.optionalCast<model::Building>()){
    if (index == OS_BuildingFields::SpaceTypeName){
      detachOtherModelObjects();
      attachOtherModelObjects(spaceLoadInstance);
      emit itemIds(makeVector());
    }else if (index == OS_BuildingFields::DefaultScheduleSetName){
      detachOtherModelObjects();
      attachOtherModelObjects(spaceLoadInstance);
      emit itemIds(makeVector());
    }
  }else if (modelObject.optionalCast<model::DefaultScheduleSet>()){
    emit itemIds(makeVector());
  }
}

std::vector<OSItemId> SpaceLoadInstanceScheduleVectorController::makeVector()
{
  std::vector<OSItemId> result;
  if (m_modelObject){
    if (!m_modelObject->handle().isNull()){

      boost::optional<model::Schedule> schedule;
      bool isDefaulted = false;
      if (m_modelObject->optionalCast<model::People>()){
        schedule = m_modelObject->cast<model::People>().numberofPeopleSchedule();
        isDefaulted = m_modelObject->cast<model::People>().isNumberofPeopleScheduleDefaulted();
      }else if (m_modelObject->optionalCast<model::Lights>()){
        schedule = m_modelObject->cast<model::Lights>().schedule();
        isDefaulted = m_modelObject->cast<model::Lights>().isScheduleDefaulted();
      }else if (m_modelObject->optionalCast<model::Luminaire>()){
        schedule = m_modelObject->cast<model::Luminaire>().schedule();
        isDefaulted = m_modelObject->cast<model::Luminaire>().isScheduleDefaulted();
      }else if (m_modelObject->optionalCast<model::ElectricEquipment>()){
        schedule = m_modelObject->cast<model::ElectricEquipment>().schedule();
        isDefaulted = m_modelObject->cast<model::ElectricEquipment>().isScheduleDefaulted();
      }else if (m_modelObject->optionalCast<model::GasEquipment>()){
        schedule = m_modelObject->cast<model::GasEquipment>().schedule();
        isDefaulted = m_modelObject->cast<model::GasEquipment>().isScheduleDefaulted();
      }else if (m_modelObject->optionalCast<model::HotWaterEquipment>()){
        schedule = m_modelObject->cast<model::HotWaterEquipment>().schedule();
        isDefaulted = m_modelObject->cast<model::HotWaterEquipment>().isScheduleDefaulted();
      }else if (m_modelObject->optionalCast<model::SteamEquipment>()){
        schedule = m_modelObject->cast<model::SteamEquipment>().schedule();
        isDefaulted = m_modelObject->cast<model::SteamEquipment>().isScheduleDefaulted();
      }else if (m_modelObject->optionalCast<model::OtherEquipment>()){
        schedule = m_modelObject->cast<model::OtherEquipment>().schedule();
        isDefaulted = m_modelObject->cast<model::OtherEquipment>().isScheduleDefaulted();
      }else if (m_modelObject->optionalCast<model::InternalMass>()){

      }

      if (schedule){
        OSItemId itemId = modelObjectToItemId(*schedule, isDefaulted);
        result.push_back(itemId);
      }
    }
  }
  return result;
}

void SpaceLoadInstanceScheduleVectorController::onRemoveItem(OSItem* item)
{
  if (m_modelObject){
    if (m_modelObject->optionalCast<model::People>()){
      m_modelObject->cast<model::People>().resetNumberofPeopleSchedule();
    }else if (m_modelObject->optionalCast<model::Lights>()){
      m_modelObject->cast<model::Lights>().resetSchedule();
    }else if (m_modelObject->optionalCast<model::Luminaire>()){
      m_modelObject->cast<model::Luminaire>().resetSchedule();
    }else if (m_modelObject->optionalCast<model::ElectricEquipment>()){
      m_modelObject->cast<model::ElectricEquipment>().resetSchedule();
    }else if (m_modelObject->optionalCast<model::GasEquipment>()){
      m_modelObject->cast<model::GasEquipment>().resetSchedule();
    }else if (m_modelObject->optionalCast<model::HotWaterEquipment>()){
      m_modelObject->cast<model::HotWaterEquipment>().resetSchedule();
    }else if (m_modelObject->optionalCast<model::SteamEquipment>()){
      m_modelObject->cast<model::SteamEquipment>().resetSchedule();
    }else if (m_modelObject->optionalCast<model::OtherEquipment>()){
      m_modelObject->cast<model::OtherEquipment>().resetSchedule();
    }else if (m_modelObject->optionalCast<model::InternalMass>()){
    }
  }
}

void SpaceLoadInstanceScheduleVectorController::onReplaceItem(OSItem * currentItem, const OSItemId& replacementItemId)
{
  onDrop(replacementItemId);
}

void SpaceLoadInstanceScheduleVectorController::onDrop(const OSItemId& itemId)
{
  if (m_modelObject){
    model::SpaceLoadInstance spaceLoadInstance = m_modelObject->cast<model::SpaceLoadInstance>();
    boost::optional<model::ModelObject> modelObject = this->getModelObject(itemId);
    if (modelObject){
      if (modelObject->optionalCast<model::Schedule>()){
        if (this->fromComponentLibrary(itemId)){
          modelObject = modelObject->clone(m_modelObject->model());
        }

        model::Schedule schedule = modelObject->cast<model::Schedule>();

        if (m_modelObject->optionalCast<model::People>()){
          m_modelObject->cast<model::People>().setNumberofPeopleSchedule(schedule);
        }else if (m_modelObject->optionalCast<model::Lights>()){
          m_modelObject->cast<model::Lights>().setSchedule(schedule);
        }else if (m_modelObject->optionalCast<model::Luminaire>()){
          m_modelObject->cast<model::Luminaire>().setSchedule(schedule);
        }else if (m_modelObject->optionalCast<model::ElectricEquipment>()){
          m_modelObject->cast<model::ElectricEquipment>().setSchedule(schedule);
        }else if (m_modelObject->optionalCast<model::GasEquipment>()){
          m_modelObject->cast<model::GasEquipment>().setSchedule(schedule);
        }else if (m_modelObject->optionalCast<model::HotWaterEquipment>()){
          m_modelObject->cast<model::HotWaterEquipment>().setSchedule(schedule);
        }else if (m_modelObject->optionalCast<model::SteamEquipment>()){
          m_modelObject->cast<model::SteamEquipment>().setSchedule(schedule);
        }else if (m_modelObject->optionalCast<model::OtherEquipment>()){
          m_modelObject->cast<model::OtherEquipment>().setSchedule(schedule);
        }else if (m_modelObject->optionalCast<model::InternalMass>()){
        }
      }
    }
  }
}

/****************************************************************************************************************************
*                                    SpaceLoadInstanceActivityScheduleVectorController                                      *
****************************************************************************************************************************/

// openstudio::IddObjectType::OS_People

void SpaceLoadInstanceActivityScheduleVectorController::onChangeRelationship(const model::ModelObject& modelObject, int index, Handle newHandle, Handle oldHandle)
{
  if(index == OS_PeopleFields::ActivityLevelScheduleName){
      emit itemIds(makeVector());
  }
}

std::vector<OSItemId> SpaceLoadInstanceActivityScheduleVectorController::makeVector()
{
  std::vector<OSItemId> result;
  if(m_modelObject){
    if(m_modelObject->optionalCast<model::People>()){
      model::People people = m_modelObject->cast<model::People>();
      boost::optional<model::Schedule> schedule = people.activityLevelSchedule();
      if (schedule){
        result.push_back(modelObjectToItemId(*schedule, false));
      }
    }
  }
  return result;
}

void SpaceLoadInstanceActivityScheduleVectorController::onRemoveItem(OSItem* item)
{
  if (m_modelObject){
    if (m_modelObject->optionalCast<model::People>()){
      m_modelObject->cast<model::People>().resetActivityLevelSchedule();
    }
  }
}

void SpaceLoadInstanceActivityScheduleVectorController::onReplaceItem(OSItem * currentItem, const OSItemId& replacementItemId)
{
  onDrop(replacementItemId);
}

void SpaceLoadInstanceActivityScheduleVectorController::onDrop(const OSItemId& itemId)
{
  if (m_modelObject){
    if(m_modelObject->optionalCast<model::People>()){
      model::People people = m_modelObject->cast<model::People>();
      boost::optional<model::ModelObject> modelObject = this->getModelObject(itemId);
      if (modelObject){
        if (modelObject->optionalCast<model::Schedule>()){
          if (this->fromComponentLibrary(itemId)){
            modelObject = modelObject->clone(m_modelObject->model());
          }
          model::Schedule schedule = modelObject->cast<model::Schedule>();
          people.setActivityLevelSchedule(schedule);
        }
      }
    }
  }
}

/****************************************************************************************************************************
*                                                 SpaceLoadInstanceMiniView                                                 *
****************************************************************************************************************************/

SpaceLoadInstanceMiniView::SpaceLoadInstanceMiniView(const model::SpaceLoadInstance& spaceLoadInstance, bool isDefault)
  : m_definitionVectorController(nullptr), m_scheduleVectorController(nullptr), m_spaceLoadInstance(spaceLoadInstance)
{
  this->setObjectName("SpaceLoadInstanceMiniView");

  auto mainGridLayout = new QGridLayout();
  this->setLayout(mainGridLayout);

  // top row
  auto hLayout = new QHBoxLayout();

  // icon
  static QIcon defaultIcon(":images/bug.png");
  QIcon icon(defaultIcon);
  const QPixmap* pixMap = IconLibrary::Instance().findMiniIcon(m_spaceLoadInstance.iddObjectType().value());
  if (pixMap){
    icon = QIcon(*pixMap);
  }

  auto label = new QLabel();
  label->setPixmap(icon.pixmap(QSize(24,24)));
  hLayout->addWidget(label);

  // name
  label = new QLabel();
  label->setText("Name: ");
  label->setStyleSheet("QLabel { font: bold; }");
  hLayout->addWidget(label);

  m_nameEdit = new OSLineEdit2();
  // m_nameEdit->bind(m_spaceLoadInstance, "name");
  opt_spaceLoadInstance = m_spaceLoadInstance;
  m_nameEdit->bind(
    *opt_spaceLoadInstance,
    OptionalStringGetter(std::bind(&model::SpaceLoadInstance::name, opt_spaceLoadInstance.get_ptr(),true)),
    boost::optional<StringSetter>(std::bind(&model::SpaceLoadInstance::setName, opt_spaceLoadInstance.get_ptr(),std::placeholders::_1))
  );

  if (isDefault){
    m_nameEdit->setEnabled(false);
  }
  hLayout->addWidget(m_nameEdit, 1);

  // remove button
  m_removeButton = new QPushButton(this);
  m_removeButton->setFlat(true);
  m_removeButton->setObjectName("DeleteButton");
  m_removeButton->setFixedSize(24,24);
  if (isDefault){
    m_removeButton->setVisible(false);
  }
  hLayout->addWidget(m_removeButton);

  connect(m_removeButton, &QPushButton::clicked, this, &SpaceLoadInstanceMiniView::onRemoveClicked);

  // inherited label
  label = new QLabel();
  label->setText("(Inherited)");
  label->setObjectName("H2");
  hLayout->addWidget(label);
  if (!isDefault){
    label->setVisible(false);
  }

  mainGridLayout->addLayout(hLayout,0,0,1,3);

  // bottom row

  // multiplier
  auto vLayout = new QVBoxLayout();

  label = new QLabel();
  label->setText("Multiplier: ");
  label->setObjectName("H2");
  vLayout->addWidget(label);

  m_multiplierEdit = new OSDoubleEdit2();
  m_multiplierEdit->setFixedWidth(60);

  // m_multiplierEdit->bind(m_spaceLoadInstance, "multiplier", std::string("isMultiplierDefaulted"));
  m_multiplierEdit->bind(
    *opt_spaceLoadInstance,
    DoubleGetter(std::bind(&model::SpaceLoadInstance::multiplier, opt_spaceLoadInstance.get_ptr())),
	boost::optional<DoubleSetter>(),
    boost::none,
    boost::none,
    boost::none,
    boost::optional<BasicQuery>(std::bind(&model::SpaceLoadInstance::isMultiplierDefaulted, opt_spaceLoadInstance.get_ptr())),
	boost::none,
	boost::none
  );

  if (isDefault){
    m_multiplierEdit->setEnabled(false);
  }
  vLayout->addWidget(m_multiplierEdit);

  vLayout->addStretch();

  mainGridLayout->addLayout(vLayout,1,0);

  // definition
  vLayout = new QVBoxLayout();

  label = new QLabel();
  label->setText("Definition: ");
  label->setObjectName("H2");
  vLayout->addWidget(label);

  m_definitionVectorController = new SpaceLoadInstanceDefinitionVectorController();
  m_definitionVectorController->attach(spaceLoadInstance);
  m_definitionDropZone = new OSDropZone(m_definitionVectorController);
  m_definitionDropZone->setMinItems(1);
  m_definitionDropZone->setMaxItems(1);
  if (isDefault){
    m_definitionDropZone->setItemsRemoveable(false);
    m_definitionDropZone->setItemsAcceptDrops(false);
  }else{
    m_definitionDropZone->setItemsRemoveable(false);
    m_definitionDropZone->setItemsAcceptDrops(true);
  }
  vLayout->addWidget(m_definitionDropZone);

  vLayout->addStretch();

  mainGridLayout->addLayout(vLayout,1,1);

  // schedule
  auto scheduleStack = new QStackedWidget();
  scheduleStack->setContentsMargins(0,0,0,0);

  auto noScheduleWidget = new QWidget();
  noScheduleWidget->setContentsMargins(0,0,0,0);
  int noScheduleIndex = scheduleStack->addWidget(noScheduleWidget);

  auto scheduleWidget = new QWidget();
  vLayout = new QVBoxLayout();
  vLayout->setContentsMargins(0,0,0,0);
  scheduleWidget->setLayout(vLayout);
  scheduleWidget->setContentsMargins(0,0,0,0);
  int scheduleIndex = scheduleStack->addWidget(scheduleWidget);

  label = new QLabel();
  label->setText("Schedule: ");
  label->setObjectName("H2");
  vLayout->addWidget(label);

  m_scheduleVectorController = new SpaceLoadInstanceScheduleVectorController();
  m_scheduleVectorController->attach(spaceLoadInstance);
  m_scheduleDropZone = new OSDropZone(m_scheduleVectorController);
  m_scheduleDropZone->setMinItems(0);
  m_scheduleDropZone->setMaxItems(1);
  if (isDefault){
    m_scheduleDropZone->setItemsRemoveable(false);
    m_scheduleDropZone->setItemsAcceptDrops(false);
  }else{
    m_scheduleDropZone->setItemsRemoveable(true);
    m_scheduleDropZone->setItemsAcceptDrops(true);
  }
  vLayout->addWidget(m_scheduleDropZone);

  vLayout->addStretch();

  mainGridLayout->addWidget(scheduleStack,1,2);

  if (spaceLoadInstance.optionalCast<model::InternalMass>()){
    scheduleStack->setCurrentIndex(noScheduleIndex);
  }else{
    scheduleStack->setCurrentIndex(scheduleIndex);
  }

  // activity schedule
  vLayout = new QVBoxLayout();

  m_activityScheduleLabel = new QLabel();
  m_activityScheduleLabel->setText("Activity Schedule: ");
  m_activityScheduleLabel->setObjectName("H2");
  vLayout->addWidget(m_activityScheduleLabel);

  m_activityScheduleVectorController = new SpaceLoadInstanceActivityScheduleVectorController();
  m_activityScheduleVectorController->attach(m_spaceLoadInstance);
  m_activityScheduleDropZone = new OSDropZone(m_activityScheduleVectorController);
  m_activityScheduleDropZone->setMinItems(1);
  m_activityScheduleDropZone->setMaxItems(1);
  if(isDefault){
    m_activityScheduleDropZone->setItemsRemoveable(false);
    m_activityScheduleDropZone->setItemsAcceptDrops(false);
  }else{
    m_activityScheduleDropZone->setItemsRemoveable(false);
    m_activityScheduleDropZone->setItemsAcceptDrops(true);
  }
  vLayout->addWidget(m_activityScheduleDropZone);

  vLayout->addStretch();

  mainGridLayout->addLayout(vLayout,1,3);

  mainGridLayout->setRowMinimumHeight(0, 30);
  mainGridLayout->setRowMinimumHeight(1, 30);

  QTimer::singleShot(0, m_definitionVectorController, SLOT(reportItems()));
  QTimer::singleShot(0, m_scheduleVectorController, SLOT(reportItems()));

  if (spaceLoadInstance.optionalCast<model::People>()){
    QTimer::singleShot(0, m_activityScheduleVectorController, SLOT(reportItems()));
  }
  else{
    m_activityScheduleDropZone->hide();
    m_activityScheduleLabel->hide();
  }

}

model::SpaceLoadInstance SpaceLoadInstanceMiniView::spaceLoadInstance() const
{
  return m_spaceLoadInstance;
}

bool SpaceLoadInstanceMiniView::isDefault() const
{
  return m_isDefault;
}

void SpaceLoadInstanceMiniView::onRemoveClicked()
{
  emit removeClicked(this);
}

// NewSpaceLoadVectorController

std::vector<OSItemId> NewSpaceLoadVectorController::makeVector()
{
  // always empty
  return std::vector<OSItemId>();
}

void NewSpaceLoadVectorController::onDrop(const OSItemId& itemId)
{
  if (m_modelObject){
    boost::optional<model::ModelObject> modelObject = this->getModelObject(itemId);
    if (modelObject){
      if (modelObject->optionalCast<model::SpaceLoadDefinition>()){
        if (this->fromComponentLibrary(itemId)){
          modelObject = modelObject->clone(m_modelObject->model());
        }

        boost::optional<model::SpaceLoadInstance> newInstance;
        if (modelObject->optionalCast<model::PeopleDefinition>()){
          newInstance = model::People(modelObject->cast<model::PeopleDefinition>());
        }else if (modelObject->optionalCast<model::LightsDefinition>()){
          newInstance = model::Lights(modelObject->cast<model::LightsDefinition>());
        }else if (modelObject->optionalCast<model::LuminaireDefinition>()){
          newInstance = model::Luminaire(modelObject->cast<model::LuminaireDefinition>());
        }else if (modelObject->optionalCast<model::ElectricEquipmentDefinition>()){
          newInstance = model::ElectricEquipment(modelObject->cast<model::ElectricEquipmentDefinition>());
        }else if (modelObject->optionalCast<model::GasEquipmentDefinition>()){
          newInstance = model::GasEquipment(modelObject->cast<model::GasEquipmentDefinition>());
        }else if (modelObject->optionalCast<model::HotWaterEquipmentDefinition>()){
          newInstance = model::HotWaterEquipment(modelObject->cast<model::HotWaterEquipmentDefinition>());
        }else if (modelObject->optionalCast<model::SteamEquipmentDefinition>()){
          newInstance = model::SteamEquipment(modelObject->cast<model::SteamEquipmentDefinition>());
        }else if (modelObject->optionalCast<model::OtherEquipmentDefinition>()){
          newInstance = model::OtherEquipment(modelObject->cast<model::OtherEquipmentDefinition>());
        }else if (modelObject->optionalCast<model::InternalMassDefinition>()){
          newInstance = model::InternalMass(modelObject->cast<model::InternalMassDefinition>());
        }

        if (newInstance){
          if (m_modelObject->optionalCast<model::SpaceType>()){
            newInstance->setSpaceType(m_modelObject->cast<model::SpaceType>());
          }else if (m_modelObject->optionalCast<model::Space>()){
            newInstance->setSpace(m_modelObject->cast<model::Space>());
          }
        }
      }
    }
  }
}

// SpaceLoadInstancesWidget

SpaceLoadInstancesWidget::SpaceLoadInstancesWidget(QWidget* parent)
  : QWidget(parent), m_newSpaceLoadVectorController(nullptr), m_newSpaceLoadDropZone(nullptr), m_dirty(false)
{
  this->setObjectName("GrayWidget");

  m_mainVLayout = new QVBoxLayout();
  m_mainVLayout->setContentsMargins(0,0,0,0);
  m_mainVLayout->setSpacing(10);
  setLayout(m_mainVLayout);
}

void SpaceLoadInstancesWidget::detach()
{
  if (m_space){
      m_space->getImpl<model::detail::ModelObject_Impl>().get()->onRelationshipChange.disconnect<SpaceLoadInstancesWidget, &SpaceLoadInstancesWidget::onSpaceRelationshipChange>(this);
    m_space.reset();
  }

  if (m_spaceType){
    m_spaceType->getImpl<model::detail::ModelObject_Impl>().get()->onRelationshipChange.disconnect<SpaceLoadInstancesWidget, &SpaceLoadInstancesWidget::onSpaceRelationshipChange>(this);
    m_spaceType.reset();
  }

  if (m_model){
    model::Building building = m_model->getUniqueModelObject<model::Building>();
      building.getImpl<model::detail::ModelObject_Impl>().get()->onRelationshipChange.disconnect<SpaceLoadInstancesWidget, &SpaceLoadInstancesWidget::onBuildingRelationshipChange>(this);

    for (model::SpaceType spaceType : m_model->getConcreteModelObjects<model::SpaceType>()){
      spaceType.getImpl<model::detail::ModelObject_Impl>().get()->onRelationshipChange.disconnect<SpaceLoadInstancesWidget, &SpaceLoadInstancesWidget::onSpaceTypeRelationshipChange>(this);
    }

    // m_model->getImpl<model::detail::Model_Impl>().get()->addWorkspaceObjectPtr.disconnect<SpaceLoadInstancesWidget, &SpaceLoadInstancesWidget::objectAdded>(this);
    connect(OSAppBase::instance(), &OSAppBase::workspaceObjectAddedPtr, this, &SpaceLoadInstancesWidget::objectAdded, Qt::QueuedConnection);

    // m_model->getImpl<openstudio::model::detail::Model_Impl>().get()->removeWorkspaceObjectPtr.disconnect<SpaceLoadInstancesWidget, &SpaceLoadInstancesWidget::objectRemoved>(this);
    connect(OSAppBase::instance(), &OSAppBase::workspaceObjectRemovedPtr, this, &SpaceLoadInstancesWidget::objectRemoved, Qt::QueuedConnection);

    m_model.reset();
  }

  m_dirty = true;
  QTimer::singleShot(0, this, SLOT(refresh()));
}

void SpaceLoadInstancesWidget::attach(const model::Space& space)
{
  detach();

  m_space = space;
  m_model = space.model();

  // m_model->getImpl<model::detail::Model_Impl>().get()->addWorkspaceObjectPtr.connect<SpaceLoadInstancesWidget, &SpaceLoadInstancesWidget::objectAdded>(this);
  connect(OSAppBase::instance(), &OSAppBase::workspaceObjectAddedPtr, this, &SpaceLoadInstancesWidget::objectAdded, Qt::QueuedConnection);

  //m_model->getImpl<openstudio::model::detail::Model_Impl>().get()->removeWorkspaceObjectPtr.connect<SpaceLoadInstancesWidget, &SpaceLoadInstancesWidget::objectRemoved>(this);
  connect(OSAppBase::instance(), &OSAppBase::workspaceObjectRemovedPtr, this, &SpaceLoadInstancesWidget::objectRemoved, Qt::QueuedConnection);

  model::Building building = m_model->getUniqueModelObject<model::Building>();
  building.getImpl<model::detail::ModelObject_Impl>().get()->onRelationshipChange.connect<SpaceLoadInstancesWidget, &SpaceLoadInstancesWidget::onBuildingRelationshipChange>(this);

  for (model::SpaceType spaceType : m_model->getConcreteModelObjects<model::SpaceType>()){
    spaceType.getImpl<model::detail::ModelObject_Impl>().get()->onRelationshipChange.connect<SpaceLoadInstancesWidget, &SpaceLoadInstancesWidget::onSpaceTypeRelationshipChange>(this);
  }

  m_space->getImpl<model::detail::ModelObject_Impl>().get()->onRelationshipChange.connect<SpaceLoadInstancesWidget, &SpaceLoadInstancesWidget::onSpaceRelationshipChange>(this);

  m_dirty = true;
  QTimer::singleShot(0, this, SLOT(refresh()));
}

void SpaceLoadInstancesWidget::attach(const model::SpaceType& spaceType)
{
  detach();

  m_spaceType = spaceType;
  m_model = spaceType.model();

  // m_model->getImpl<model::detail::Model_Impl>().get()->addWorkspaceObjectPtr.connect<SpaceLoadInstancesWidget, &SpaceLoadInstancesWidget::objectAdded>(this);
  connect(OSAppBase::instance(), &OSAppBase::workspaceObjectAddedPtr, this, &SpaceLoadInstancesWidget::objectAdded, Qt::QueuedConnection);

  //m_model->getImpl<model::detail::Model_Impl>().get()->removeWorkspaceObjectPtr.connect<SpaceLoadInstancesWidget, &SpaceLoadInstancesWidget::objectRemoved>(this);
  connect(OSAppBase::instance(), &OSAppBase::workspaceObjectRemovedPtr, this, &SpaceLoadInstancesWidget::objectRemoved, Qt::QueuedConnection);

  model::Building building = m_model->getUniqueModelObject<model::Building>();
  building.getImpl<model::detail::ModelObject_Impl>().get()->onRelationshipChange.connect<SpaceLoadInstancesWidget, &SpaceLoadInstancesWidget::onBuildingRelationshipChange>(this);

  for (model::SpaceType spaceType : m_model->getConcreteModelObjects<model::SpaceType>()){
    spaceType.getImpl<model::detail::ModelObject_Impl>().get()->onRelationshipChange.connect<SpaceLoadInstancesWidget, &SpaceLoadInstancesWidget::onSpaceTypeRelationshipChange>(this);
  }

  m_dirty = true;
  QTimer::singleShot(0, this, SLOT(refresh()));
}

void SpaceLoadInstancesWidget::remove(SpaceLoadInstanceMiniView* spaceLoadInstanceMiniView)
{
  spaceLoadInstanceMiniView->spaceLoadInstance().remove();
}

void SpaceLoadInstancesWidget::onBuildingRelationshipChange(int index, Handle newHandle, Handle oldHandle)
{
  if (newHandle == oldHandle){
    return;
  }

  if (index == OS_BuildingFields::SpaceTypeName){
    m_dirty = true;
    QTimer::singleShot(0, this, SLOT(refresh()));
  }
}

void SpaceLoadInstancesWidget::onSpaceTypeRelationshipChange(int index, Handle newHandle, Handle oldHandle)
{
  if (newHandle == oldHandle){
    return;
  }
}

void SpaceLoadInstancesWidget::onSpaceRelationshipChange(int index, Handle newHandle, Handle oldHandle)
{
  if (newHandle == oldHandle){
    return;
  }

  if (index == OS_SpaceFields::SpaceTypeName){
    m_dirty = true;
    QTimer::singleShot(0, this, SLOT(refresh()));
  }
}

void SpaceLoadInstancesWidget::objectAdded(std::shared_ptr<openstudio::detail::WorkspaceObject_Impl> impl, const openstudio::IddObjectType& iddObjectType, const openstudio::UUID& handle)
{
  if (iddObjectType == IddObjectType::OS_SpaceType){
    impl.get()->detail::WorkspaceObject_Impl::onRelationshipChange.connect<SpaceLoadInstancesWidget, &SpaceLoadInstancesWidget::onSpaceTypeRelationshipChange>(this);
    return;
  }

  std::shared_ptr<model::detail::SpaceLoadInstance_Impl> spaceLoadInstanceImpl = std::dynamic_pointer_cast<model::detail::SpaceLoadInstance_Impl>(impl);
  if (spaceLoadInstanceImpl){

    boost::optional<model::SpaceType> spaceType = m_spaceType;
    if (m_space){
      spaceType = m_space->spaceType();

      if (spaceLoadInstanceImpl->space()){
        if (m_space->handle() == spaceLoadInstanceImpl->space()->handle()){
          m_dirty = true;
          QTimer::singleShot(0, this, SLOT(refresh()));
          return;
        }
      }
    }

    if (spaceType){
      if (spaceLoadInstanceImpl->spaceType()){
        if (spaceType->handle() == spaceLoadInstanceImpl->spaceType()->handle()){
          m_dirty = true;
          QTimer::singleShot(0, this, SLOT(refresh()));
          return;
        }
      }
    }
  }
}

void SpaceLoadInstancesWidget::objectRemoved(std::shared_ptr<openstudio::detail::WorkspaceObject_Impl> impl, const openstudio::IddObjectType& iddObjectType, const openstudio::UUID& handle)
{
  std::shared_ptr<model::detail::SpaceLoadInstance_Impl> spaceLoadInstanceImpl = std::dynamic_pointer_cast<model::detail::SpaceLoadInstance_Impl>(impl);
  if (spaceLoadInstanceImpl){
    m_dirty = true;
    QTimer::singleShot(0, this, SLOT(refresh()));
  }
}

void SpaceLoadInstancesWidget::refresh()
{
  if (!m_dirty){
    return;
  }
  m_dirty = false;

  QLayoutItem *child;
  while ((child = m_mainVLayout->takeAt(0)) != nullptr) {
    QWidget* widget = child->widget();
    if (widget){
      delete widget;
    }
    delete child;
  }

  // existing m_newSpaceLoadDropZone and m_newSpaceLoadVectorController were deleted above
  m_newSpaceLoadVectorController = nullptr;
  m_newSpaceLoadDropZone = nullptr;

  m_newSpaceLoadVectorController = new NewSpaceLoadVectorController();

  if (m_space){
    m_newSpaceLoadVectorController->attach(*m_space);

    boost::optional<model::SpaceType> spaceType = m_space->spaceType();
    if (spaceType){
      addSpaceTypeLoads(*spaceType, true);
    }
    addSpaceLoads(*m_space);

  }else if (m_spaceType){
    m_newSpaceLoadVectorController->attach(*m_spaceType);

    addSpaceTypeLoads(*m_spaceType, false);
  }

  // separator
  QFrame * line;
  line = new QFrame();
  line->setFrameShape(QFrame::HLine);
  line->setFrameShadow(QFrame::Sunken);
  m_mainVLayout->addWidget(line);

  // new load drop zone
  auto hLayout = new QHBoxLayout();
  hLayout->setContentsMargins(0,0,0,0);
  hLayout->setSpacing(10);
  auto vLayout = new QVBoxLayout();
  vLayout->setContentsMargins(0,0,0,0);
  vLayout->setSpacing(10);

  auto label = new QLabel();
  label->setText("Add New Load:");
  label->setObjectName("H2");
  vLayout->addWidget(label);

  m_newSpaceLoadDropZone = new OSDropZone(m_newSpaceLoadVectorController);
  vLayout->addWidget(m_newSpaceLoadDropZone, 1);
  hLayout->addLayout(vLayout);

  auto widget = new QWidget();
  widget->setLayout(hLayout);

  m_mainVLayout->addWidget(widget);
}

void SpaceLoadInstancesWidget::addSpaceLoads(const model::Space& space)
{
  // follow same order in LoadsController and LoadsTreeItem
  std::vector<model::ModelObject> spaceLoads;

  std::vector<model::People> people = space.people();
  std::sort(people.begin(), people.end(), WorkspaceObjectNameLess());
  spaceLoads.insert(spaceLoads.end(), people.begin(), people.end());

  std::vector<model::Lights> lights = space.lights();
  std::sort(lights.begin(), lights.end(), WorkspaceObjectNameLess());
  spaceLoads.insert(spaceLoads.end(), lights.begin(), lights.end());

  std::vector<model::Luminaire> luminaires = space.luminaires();
  std::sort(luminaires.begin(), luminaires.end(), WorkspaceObjectNameLess());
  spaceLoads.insert(spaceLoads.end(), luminaires.begin(), luminaires.end());

  std::vector<model::ElectricEquipment> electricEquipment = space.electricEquipment();
  std::sort(electricEquipment.begin(), electricEquipment.end(), WorkspaceObjectNameLess());
  spaceLoads.insert(spaceLoads.end(), electricEquipment.begin(), electricEquipment.end());

  std::vector<model::GasEquipment> gasEquipment = space.gasEquipment();
  std::sort(gasEquipment.begin(), gasEquipment.end(), WorkspaceObjectNameLess());
  spaceLoads.insert(spaceLoads.end(), gasEquipment.begin(), gasEquipment.end());

  std::vector<model::SteamEquipment> steamEquipment = space.steamEquipment();
  std::sort(steamEquipment.begin(), steamEquipment.end(), WorkspaceObjectNameLess());
  spaceLoads.insert(spaceLoads.end(), steamEquipment.begin(), steamEquipment.end());

  std::vector<model::OtherEquipment> otherEquipment = space.otherEquipment();
  std::sort(otherEquipment.begin(), otherEquipment.end(), WorkspaceObjectNameLess());
  spaceLoads.insert(spaceLoads.end(), otherEquipment.begin(), otherEquipment.end());

  std::vector<model::InternalMass> internalMass = space.internalMass();
  std::sort(internalMass.begin(), internalMass.end(), WorkspaceObjectNameLess());
  spaceLoads.insert(spaceLoads.end(), internalMass.begin(), internalMass.end());

  for (const model::ModelObject& modelObject : spaceLoads){
    if (!modelObject.handle().isNull()){
      if (modelObject.optionalCast<model::SpaceLoadInstance>()){

        // separator
        QFrame * line;
        line = new QFrame();
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        m_mainVLayout->addWidget(line);

        addSpaceLoadInstance(modelObject.cast<model::SpaceLoadInstance>(), false);
      }
    }
  }
}

void SpaceLoadInstancesWidget::addSpaceTypeLoads(const model::SpaceType& spaceType, bool addAsDefaultLoads)
{
// follow same order in LoadsController and LoadsTreeItem
  std::vector<model::ModelObject> spaceLoads;

  std::vector<model::People> people = spaceType.people();
  std::sort(people.begin(), people.end(), WorkspaceObjectNameLess());
  spaceLoads.insert(spaceLoads.end(), people.begin(), people.end());

  std::vector<model::Lights> lights = spaceType.lights();
  std::sort(lights.begin(), lights.end(), WorkspaceObjectNameLess());
  spaceLoads.insert(spaceLoads.end(), lights.begin(), lights.end());

  std::vector<model::Luminaire> luminaires = spaceType.luminaires();
  std::sort(luminaires.begin(), luminaires.end(), WorkspaceObjectNameLess());
  spaceLoads.insert(spaceLoads.end(), luminaires.begin(), luminaires.end());

  std::vector<model::ElectricEquipment> electricEquipment = spaceType.electricEquipment();
  std::sort(electricEquipment.begin(), electricEquipment.end(), WorkspaceObjectNameLess());
  spaceLoads.insert(spaceLoads.end(), electricEquipment.begin(), electricEquipment.end());

  std::vector<model::GasEquipment> gasEquipment = spaceType.gasEquipment();
  std::sort(gasEquipment.begin(), gasEquipment.end(), WorkspaceObjectNameLess());
  spaceLoads.insert(spaceLoads.end(), gasEquipment.begin(), gasEquipment.end());

  std::vector<model::SteamEquipment> steamEquipment = spaceType.steamEquipment();
  std::sort(steamEquipment.begin(), steamEquipment.end(), WorkspaceObjectNameLess());
  spaceLoads.insert(spaceLoads.end(), steamEquipment.begin(), steamEquipment.end());

  std::vector<model::OtherEquipment> otherEquipment = spaceType.otherEquipment();
  std::sort(otherEquipment.begin(), otherEquipment.end(), WorkspaceObjectNameLess());
  spaceLoads.insert(spaceLoads.end(), otherEquipment.begin(), otherEquipment.end());

  std::vector<model::InternalMass> internalMass = spaceType.internalMass();
  std::sort(internalMass.begin(), internalMass.end(), WorkspaceObjectNameLess());
  spaceLoads.insert(spaceLoads.end(), internalMass.begin(), internalMass.end());

  for (const model::ModelObject& modelObject : spaceLoads){
    if (!modelObject.handle().isNull()){
      if (modelObject.optionalCast<model::SpaceLoadInstance>()){

        // separator
        QFrame * line;
        line = new QFrame();
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        m_mainVLayout->addWidget(line);

        addSpaceLoadInstance(modelObject.cast<model::SpaceLoadInstance>(), addAsDefaultLoads);
      }
    }
  }
}

void SpaceLoadInstancesWidget::addSpaceLoadInstance(const model::SpaceLoadInstance& spaceLoadInstance, bool isDefault)
{
  auto spaceLoadInstanceMiniView = new SpaceLoadInstanceMiniView(spaceLoadInstance, isDefault);

  connect(spaceLoadInstanceMiniView, &SpaceLoadInstanceMiniView::removeClicked, this, &SpaceLoadInstancesWidget::remove);

  m_mainVLayout->addWidget(spaceLoadInstanceMiniView);
}

} // openstudio

