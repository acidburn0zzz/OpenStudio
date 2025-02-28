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

#ifndef SHAREDGUICOMPONENTS_LOCALLIBRARYVIEW_HPP
#define SHAREDGUICOMPONENTS_LOCALLIBRARYVIEW_HPP

#include "OSDragableView.hpp"

#include "HeaderViews.hpp"

#include <QPoint>
#include <QWidget>

class QPushButton;
class QLabel;

namespace openstudio{

class MeasureBadge;
class OSViewSwitcher;

class LocalLibraryView : public QWidget
{
  Q_OBJECT

  public:

  LocalLibraryView(QWidget * parent = nullptr);

  virtual ~LocalLibraryView() {}

  OSViewSwitcher * mainViewSwitcher;

  QPushButton * duplicateMeasureButton;

  QPushButton * addMeasureButton;

  QPushButton * myMeasuresFolderButton;

  QPushButton * addBCLMeasureButton;
};

class LibraryGroupItemHeader : public LightGradientHeader
{
  Q_OBJECT

  public:

  LibraryGroupItemHeader();

  virtual ~LibraryGroupItemHeader() {}

  public slots:

  void setCount(int count);

  private:

  QLabel * countLabel;
};

class LibrarySubGroupItemHeader : public LightHeader
{
  Q_OBJECT

  public:

  LibrarySubGroupItemHeader();

  virtual ~LibrarySubGroupItemHeader() {}

  public slots:

  void setCount(int count);

  private:

  QLabel * countLabel;
};

class LibraryItemView : public OSDragableView
{
  Q_OBJECT

  public:

  LibraryItemView(QWidget * parent = nullptr);

  virtual ~LibraryItemView() {}

  QLabel * label;
  QLabel * m_measureTypeBadge;
  MeasureBadge * m_measureBadge;
  QLabel * errorLabel;

  public slots:

  void setHasEmphasis(bool hasEmphasis);

  protected:

  void paintEvent(QPaintEvent *) override;
};

} // openstudio

#endif // SHAREDGUICOMPONENTS_LOCALLIBRARYVIEW_HPP

