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

#ifndef SHAREDGUICOMPONENTS_BASEAPP_HPP
#define SHAREDGUICOMPONENTS_BASEAPP_HPP

#include "../utilities/core/Path.hpp"

#include <QWidget>
#include <boost/optional.hpp>
//#include "EditController.hpp"

namespace openstudio {
  class MeasureManager;
  class EditController;
  class Workspace;

  //namespace analysisdriver {
  //  class SimpleProject;
  //}

  namespace model {
    class Model;
  }

  class BaseApp
  {
    public:

      virtual ~BaseApp() {}

      //virtual boost::optional<analysisdriver::SimpleProject> project() = 0;
      virtual QWidget *mainWidget() = 0;
      virtual openstudio::MeasureManager &measureManager() = 0;
      virtual void updateSelectedMeasureState() = 0;

      virtual void addMeasure() = 0;
      virtual void duplicateSelectedMeasure() = 0;
      virtual void updateMyMeasures() = 0;
      virtual void updateBCLMeasures() = 0;
      virtual void downloadUpdatedBCLMeasures() = 0;
      virtual void openBclDlg() = 0;

      virtual void chooseHorizontalEditTab() = 0;
      virtual QSharedPointer<openstudio::EditController> editController() = 0;
      virtual boost::optional<openstudio::path> tempDir() = 0;
      virtual boost::optional<openstudio::model::Model> currentModel() = 0;
      //virtual boost::optional<openstudio::Workspace> currentWorkspace() = 0;
  };

}

#endif // SHAREDGUICOMPONENTS_BASEAPP_HPP
