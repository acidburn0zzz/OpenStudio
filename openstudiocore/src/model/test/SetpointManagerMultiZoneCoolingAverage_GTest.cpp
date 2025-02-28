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

#include <gtest/gtest.h>
#include "ModelFixture.hpp"
#include "../SetpointManagerMultiZoneCoolingAverage.hpp"
#include "../SetpointManagerMultiZoneCoolingAverage_Impl.hpp"
#include "../Node.hpp"
#include "../Node_Impl.hpp"
#include "../AirLoopHVAC.hpp"
#include "../PlantLoop.hpp"

using namespace openstudio::model;

TEST_F(ModelFixture, SetpointManagerMultiZoneCoolingAverage_DefaultConstructor)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";

  ASSERT_EXIT (
  {
    Model m;
    SetpointManagerMultiZoneCoolingAverage testObject(m);

    exit(0);
  } ,
    ::testing::ExitedWithCode(0), "" );
}

TEST_F(ModelFixture, SetpointManagerMultiZoneCoolingAverage_addToNode)
{
  Model m;
  AirLoopHVAC airloop(m);
  PlantLoop plantLoop(m);
  Node testObject = airloop.supplyOutletNode();

  SetpointManagerMultiZoneCoolingAverage spm_1(m);
  spm_1.setControlVariable("Temperature");

  SetpointManagerMultiZoneCoolingAverage spm_2(m);
  spm_2.setControlVariable("Temperature");

  SetpointManagerMultiZoneCoolingAverage spm_3(m);
  spm_3.setControlVariable("Temperature");

  EXPECT_TRUE(spm_1.addToNode(testObject));

  Node plantNode = plantLoop.supplyOutletNode();
  EXPECT_FALSE(spm_3.addToNode(plantNode));

  std::vector<SetpointManager> _setpointManagers = testObject.setpointManagers();
  EXPECT_EQ(1, _setpointManagers.size());
  std::vector<SetpointManagerMultiZoneCoolingAverage> SetpointManagerMultiZoneCoolingAverages = m.getModelObjects<SetpointManagerMultiZoneCoolingAverage>();
  EXPECT_EQ(3, SetpointManagerMultiZoneCoolingAverages.size());

  EXPECT_EQ(testObject, spm_1.setpointNode());
  EXPECT_TRUE(spm_2.addToNode(testObject));
  EXPECT_EQ(testObject, spm_2.setpointNode());

  _setpointManagers = testObject.setpointManagers();
  EXPECT_TRUE(std::find(_setpointManagers.begin(), _setpointManagers.end(), spm_1) == _setpointManagers.end());
  EXPECT_EQ(1, _setpointManagers.size());
  SetpointManagerMultiZoneCoolingAverages = m.getModelObjects<SetpointManagerMultiZoneCoolingAverage>();
  EXPECT_EQ(2, SetpointManagerMultiZoneCoolingAverages.size());
}

TEST_F(ModelFixture, SetpointManagerMultiZoneCoolingAverage_remove)
{
  Model m;
  AirLoopHVAC airloop(m);
  Node testObject = airloop.supplyOutletNode();

  SetpointManagerMultiZoneCoolingAverage spm(m);
  spm.setControlVariable("Temperature");

  EXPECT_TRUE(spm.addToNode(testObject));

  std::vector<SetpointManager> _setpointManagers = testObject.setpointManagers();
  EXPECT_EQ(1, _setpointManagers.size());
  std::vector<SetpointManagerMultiZoneCoolingAverage> SetpointManagerMultiZoneCoolingAverages = m.getModelObjects<SetpointManagerMultiZoneCoolingAverage>();
  EXPECT_EQ(1, SetpointManagerMultiZoneCoolingAverages.size());

  spm.remove();

  _setpointManagers = testObject.setpointManagers();
  EXPECT_EQ(0, _setpointManagers.size());
  SetpointManagerMultiZoneCoolingAverages = m.getModelObjects<SetpointManagerMultiZoneCoolingAverage>();
  EXPECT_EQ(0, SetpointManagerMultiZoneCoolingAverages.size());
}

TEST_F(ModelFixture, SetpointManagerMultiZoneCoolingAverage_clone)
{
  Model m;
  AirLoopHVAC airloop(m);
  Node outletNode = airloop.supplyOutletNode();

  SetpointManagerMultiZoneCoolingAverage testObject(m);
  testObject.setControlVariable("Temperature");
  testObject.addToNode(outletNode);
  ASSERT_TRUE(testObject.setpointNode());
  EXPECT_EQ(outletNode, testObject.setpointNode().get());

  SetpointManagerMultiZoneCoolingAverage testObjectClone = testObject.clone(m).cast<SetpointManagerMultiZoneCoolingAverage>();
  EXPECT_FALSE(testObjectClone.setpointNode());

  EXPECT_NE(testObject, testObjectClone);
  EXPECT_EQ(testObject.controlVariable(), testObjectClone.controlVariable());
  EXPECT_EQ(testObject.minimumSetpointTemperature(), testObjectClone.minimumSetpointTemperature());
  EXPECT_EQ(testObject.maximumSetpointTemperature(), testObjectClone.maximumSetpointTemperature());
  EXPECT_EQ("Temperature", testObjectClone.controlVariable());
  EXPECT_DOUBLE_EQ(12., testObjectClone.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(18., testObjectClone.maximumSetpointTemperature());
}

TEST_F(ModelFixture, SetpointManagerMultiZoneCoolingAverage_customDataClone)
{
  Model m;
  AirLoopHVAC airloop(m);
  Node outletNode = airloop.supplyOutletNode();

  SetpointManagerMultiZoneCoolingAverage testObject(m);
  testObject.setControlVariable("Temperature");
  testObject.addToNode(outletNode);
  testObject.setMinimumSetpointTemperature(0.012);
  testObject.setMaximumSetpointTemperature(0.005);
  ASSERT_TRUE(testObject.setpointNode());
  EXPECT_EQ(outletNode, testObject.setpointNode().get());

  SetpointManagerMultiZoneCoolingAverage testObjectClone = testObject.clone(m).cast<SetpointManagerMultiZoneCoolingAverage>();
  EXPECT_FALSE(testObjectClone.setpointNode());

  EXPECT_NE(testObject, testObjectClone);
  EXPECT_EQ(testObject.controlVariable(), testObjectClone.controlVariable());
  EXPECT_EQ(testObject.minimumSetpointTemperature(), testObjectClone.minimumSetpointTemperature());
  EXPECT_EQ(testObject.maximumSetpointTemperature(), testObjectClone.maximumSetpointTemperature());
  EXPECT_EQ("Temperature", testObjectClone.controlVariable());
  EXPECT_DOUBLE_EQ(0.012, testObjectClone.minimumSetpointTemperature());
  EXPECT_DOUBLE_EQ(0.005, testObjectClone.maximumSetpointTemperature());
}
