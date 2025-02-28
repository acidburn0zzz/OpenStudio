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
#include "../Model.hpp"
#include "../Model_Impl.hpp"
#include "../ConstructionWithInternalSource.hpp"
#include "../ConstructionWithInternalSource_Impl.hpp"

#include "../StandardOpaqueMaterial.hpp"
#include "../StandardOpaqueMaterial_Impl.hpp"

using namespace openstudio;
using namespace openstudio::model;

TEST(ConstructionWithInternalSource, DefaultConstructed)
{
  Model model;

  ConstructionWithInternalSource construction(model);
  EXPECT_EQ(0, construction.numLayers());
  EXPECT_EQ(0, construction.layers().size());
  EXPECT_EQ(1, construction.sourcePresentAfterLayerNumber());
  EXPECT_EQ(1, construction.temperatureCalculationRequestedAfterLayerNumber());
  EXPECT_EQ(1, construction.dimensionsForTheCTFCalculation());
  EXPECT_EQ(0.154, construction.tubeSpacing());
}

TEST(ConstructionWithInternalSource, FromLayers)
{
  Model model;

  // Create some materials
  StandardOpaqueMaterial exterior(model);
  StandardOpaqueMaterial interior(model);

  OpaqueMaterialVector layers;

  EXPECT_EQ(0, model.getModelObjects<ConstructionWithInternalSource>().size());

  EXPECT_EQ(0, layers.size());
  EXPECT_THROW((ConstructionWithInternalSource(layers)), std::exception);

  EXPECT_EQ(0, model.getModelObjects<ConstructionWithInternalSource>().size());

  layers.push_back(exterior);

  EXPECT_EQ(1u, layers.size());
  EXPECT_THROW((ConstructionWithInternalSource(layers)), std::exception);

  EXPECT_EQ(0, model.getModelObjects<ConstructionWithInternalSource>().size());

  layers.push_back(interior);

  EXPECT_EQ(2u, layers.size());
  ConstructionWithInternalSource construction(layers);
  EXPECT_EQ(2u, construction.numLayers());
  EXPECT_EQ(2u, construction.layers().size());
  EXPECT_EQ(1, construction.sourcePresentAfterLayerNumber());
  EXPECT_EQ(1, construction.temperatureCalculationRequestedAfterLayerNumber());
  EXPECT_EQ(1, construction.dimensionsForTheCTFCalculation());
  EXPECT_EQ(0.154, construction.tubeSpacing());

  // check that we can't mess up the construction
  EXPECT_FALSE(construction.setSourcePresentAfterLayerNumber(3));
  EXPECT_EQ(1, construction.sourcePresentAfterLayerNumber());
  EXPECT_FALSE(construction.setTemperatureCalculationRequestedAfterLayerNumber(3));
  EXPECT_EQ(1, construction.temperatureCalculationRequestedAfterLayerNumber());

  EXPECT_TRUE(construction.eraseLayer(1));
  EXPECT_EQ(1u, construction.numLayers());

  EXPECT_FALSE(construction.setLayers(MaterialVector()));
  EXPECT_EQ(1u, construction.numLayers());

  MaterialVector testLayers = construction.layers();
  ASSERT_EQ(static_cast<unsigned>(1),testLayers.size());
  EXPECT_TRUE(testLayers[0] == exterior);

  testLayers.push_back(interior);
  testLayers.push_back(exterior);

  EXPECT_TRUE(construction.setLayers(testLayers));
  EXPECT_EQ(3u, construction.numLayers());

  testLayers = construction.layers();
  ASSERT_EQ(static_cast<unsigned>(3),testLayers.size());
  EXPECT_TRUE(testLayers[0] == exterior);
  EXPECT_TRUE(testLayers[1] == interior);
  EXPECT_TRUE(testLayers[2] == exterior);

  EXPECT_TRUE(construction.setSourcePresentAfterLayerNumber(3));
  EXPECT_EQ(3, construction.sourcePresentAfterLayerNumber());
  EXPECT_TRUE(construction.setTemperatureCalculationRequestedAfterLayerNumber(3));
  EXPECT_EQ(3, construction.temperatureCalculationRequestedAfterLayerNumber());

  testLayers.clear();
  testLayers.push_back(interior);
  testLayers.push_back(exterior);

  EXPECT_TRUE(construction.setLayers(testLayers));
  EXPECT_EQ(2u, construction.numLayers());

  testLayers = construction.layers();
  ASSERT_EQ(static_cast<unsigned>(2),testLayers.size());
  EXPECT_TRUE(testLayers[0] == interior);
  EXPECT_TRUE(testLayers[1] == exterior);

  EXPECT_EQ(1, construction.sourcePresentAfterLayerNumber());
  EXPECT_EQ(1, construction.temperatureCalculationRequestedAfterLayerNumber());

  EXPECT_FALSE(construction.setSourcePresentAfterLayerNumber(3));
  EXPECT_EQ(1, construction.sourcePresentAfterLayerNumber());
  EXPECT_FALSE(construction.setTemperatureCalculationRequestedAfterLayerNumber(3));
  EXPECT_EQ(1, construction.temperatureCalculationRequestedAfterLayerNumber());

  while (layers.size() < 11) {
    layers.push_back(exterior);
  }
  EXPECT_THROW((ConstructionWithInternalSource(layers)), std::exception);
}

TEST(ConstructionWithInternalSource, ReverseConstructionWithInternalSource_1)
{
  Model model;

  // Create some materials
  StandardOpaqueMaterial exterior(model);

  OpaqueMaterialVector layers;
  layers.push_back(exterior);
  layers.push_back(exterior);

  ConstructionWithInternalSource construction(layers);

  EXPECT_EQ(1u, model.getModelObjects<ConstructionWithInternalSource>().size());

  ConstructionWithInternalSource construction2 = construction.reverseConstructionWithInternalSource();

  EXPECT_EQ(1u, model.getModelObjects<ConstructionWithInternalSource>().size());
  EXPECT_EQ(construction.handle(), construction2.handle());
}

TEST(ConstructionWithInternalSource, ReverseConstructionWithInternalSource_2)
{
  Model model;

  // Create some materials
  StandardOpaqueMaterial exterior(model);
  StandardOpaqueMaterial interior(model);

  OpaqueMaterialVector layers;
  layers.push_back(exterior);
  layers.push_back(interior);

  ConstructionWithInternalSource construction(layers);

  EXPECT_EQ(1u, model.getModelObjects<ConstructionWithInternalSource>().size());

  ConstructionWithInternalSource construction2 = construction.reverseConstructionWithInternalSource();

  EXPECT_EQ(2u, model.getModelObjects<ConstructionWithInternalSource>().size());
  EXPECT_NE(construction.handle(), construction2.handle());

  MaterialVector testLayers = construction2.layers();
  ASSERT_EQ(static_cast<unsigned>(2),testLayers.size());
  EXPECT_TRUE(testLayers[0] == interior);
  EXPECT_TRUE(testLayers[1] == exterior);

  ConstructionWithInternalSource construction3 = construction.reverseConstructionWithInternalSource();
  EXPECT_EQ(2u, model.getModelObjects<ConstructionWithInternalSource>().size());
  EXPECT_NE(construction.handle(), construction3.handle());
  EXPECT_EQ(construction2.handle(), construction3.handle());
}

