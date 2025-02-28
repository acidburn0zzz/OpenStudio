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

#ifndef OPENSTUDIO_COLLAPSIBLEINSPECTOR_HPP
#define OPENSTUDIO_COLLAPSIBLEINSPECTOR_HPP

#include <QAbstractButton>
#include <QWidget>

class QLabel;
class QPaintEvent;

namespace openstudio {

class CollapsibleInspectorHeader;

class CollapsibleInspector : public QWidget
{
  Q_OBJECT

public:

  CollapsibleInspector(QString text,
    QWidget * inspector,
    QWidget * parent = nullptr);

  virtual ~CollapsibleInspector() {}

private:

  void createLayout();

  CollapsibleInspectorHeader * m_header;

  QWidget * m_inspector;

public slots:

  void on_headerToggled(bool checked);

};

class CollapsibleInspectorHeader : public QAbstractButton
{
  Q_OBJECT

public:

  CollapsibleInspectorHeader(QString text,
    QWidget * parent = nullptr);

  void setChecked(bool isChecked);

protected:

  void paintEvent(QPaintEvent * event) override;

  QSize sizeHint() const override;

private:

  void createLayout();

  void setImage(bool isChecked);

  QString m_text;

  QLabel * m_arrowLabel;

private slots:

  void on_toggled(bool checked);

};

} // openstudio

#endif // OPENSTUDIO_COLLAPSIBLEINSPECTOR_HPP

