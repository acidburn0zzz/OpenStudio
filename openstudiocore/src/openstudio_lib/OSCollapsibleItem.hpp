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

#ifndef OPENSTUDIO_OSCOLLAPSIBLEITEM_HPP
#define OPENSTUDIO_OSCOLLAPSIBLEITEM_HPP

#include <QWidget>
#include "OSItem.hpp"

class QButtonGroup;
class QComboBox;
class QLabel;
class QPushButton;
class QRadioButton;
class QVBoxLayout;

namespace openstudio {

class OSCollapsibleItemHeader;
class OSItemId;
class OSItemList;

class OSCollapsibleItem : public QWidget
{
  Q_OBJECT

  public:

    OSCollapsibleItem(OSCollapsibleItemHeader * collapsibleItemHeader,
                      OSItemList * itemList,
                      QWidget * parent = nullptr);

    virtual ~OSCollapsibleItem() {}

    bool isSelected() const;
    void setSelected(bool selected);

    bool expanded() const;
    void setExpanded(bool expanded);

    OSCollapsibleItemHeader* collapsibleItemHeader() const;

    OSItemList* itemList() const;

    bool itemsDraggable() const;
    void setItemsDraggable(bool itemsDraggable);

    bool itemsRemoveable() const;
    void setItemsRemoveable(bool itemsRemoveable);

    OSItemType itemsType() const;
    void setItemsType(OSItemType type);

    bool showFilterLayout();
    void setShowFilterLayout(const bool showFilterLayout);

  signals:

    void collapsableItemSelected(OSCollapsibleItem *);

    void itemSelected(OSItem* item);

    void itemRemoveClicked(OSItem* item);

    void itemReplacementDropped(OSItem * currentItem, const OSItemId& replacementItemId);

    void selectionCleared();

    void openLibDlgClicked();

  protected:

    void paintEvent(QPaintEvent * event) override;

  private slots:

    void onHeaderClicked(OSCollapsibleItemHeader * header);

    void filtersOnClicked();

    void filtersOffClicked();

    void comboBoxClicked(const QString & string);

  private:
    void createLayout();

    void setShowFilterWidgets(const bool showFilterWidgets);

    OSCollapsibleItemHeader * m_collapsibleItemHeader;
    OSItemList * m_itemList;
    QVBoxLayout * m_mainLayout;
    QPushButton * m_openLibDlgButton;
    QRadioButton * m_filtersOnBtn;
    QRadioButton * m_filtersOffBtn;
    QButtonGroup * m_filterBtnGroup;
    QLabel * m_sortLabel;
    QComboBox * m_sortComboBox;
    bool m_showFilterLayout;
    QWidget * m_filterWidget;
};

} // openstudio

#endif // OPENSTUDIO_OSCOLLAPSIBLEITEM_HPP
