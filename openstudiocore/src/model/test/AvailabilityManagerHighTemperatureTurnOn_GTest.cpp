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

#include <model/test/ModelFixture.hpp>

#include "../AvailabilityManagerHighTemperatureTurnOn.hpp"
#include "../AvailabilityManagerHighTemperatureTurnOn_Impl.hpp"

#include "../Node.hpp"
#include "../AirLoopHVAC.hpp"
#include "../PlantLoop.hpp"

using namespace openstudio;
using namespace openstudio::model;

TEST_F(ModelFixture, AvailabilityManagerHighTemperatureTurnOn_DefaultConstructor)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";

  ASSERT_EXIT (
  {
     Model m;
     AvailabilityManagerHighTemperatureTurnOn avm(m);

     exit(0);
  } ,
    ::testing::ExitedWithCode(0), "" );
}

TEST_F(ModelFixture, AvailabilityManagerHighTemperatureTurnOn_Setters_Getters)
{
  Model m;

  AvailabilityManagerHighTemperatureTurnOn avm(m);

  // Test Sensor node fields
  // Random node
  Node n(m);
  ASSERT_FALSE(avm.sensorNode());
  EXPECT_TRUE(avm.setSensorNode(n));
  ASSERT_TRUE(avm.sensorNode());
  ASSERT_EQ(n.handle(), avm.sensorNode()->handle());
  avm.resetSensorNode();
  ASSERT_FALSE(avm.sensorNode());

  // AirLoop Node
  AirLoopHVAC airloop(m);
  Node airLoop_Node = airloop.supplyOutletNode();
  EXPECT_TRUE(avm.setSensorNode(airLoop_Node));
  ASSERT_TRUE(avm.sensorNode());
  ASSERT_EQ(airLoop_Node.handle(), avm.sensorNode()->handle());

  // PlantLoop Node
  PlantLoop plantLoop(m);
  Node plantLoop_Node = plantLoop.supplyOutletNode();
  EXPECT_TRUE(avm.setSensorNode(plantLoop_Node));
  ASSERT_TRUE(avm.sensorNode());
  ASSERT_EQ(plantLoop_Node.handle(), avm.sensorNode()->handle());


  // Test temperature
  EXPECT_TRUE(avm.setTemperature(60.19));
  ASSERT_EQ(60.19, avm.temperature());
}
