########################################################################################################################
#  OpenStudio(R), Copyright (c) 2008-2018, Alliance for Sustainable Energy, LLC. All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
#  following conditions are met:
#
#  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
#  disclaimer.
#
#  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
#  disclaimer in the documentation and/or other materials provided with the distribution.
#
#  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
#  derived from this software without specific prior written permission from the respective party.
#
#  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
#  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
#  written permission from Alliance for Sustainable Energy, LLC.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
#  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
#  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
#  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
#  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
#  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
########################################################################################################################

require 'openstudio'

require 'minitest/autorun'

class TimeSeries_Test < MiniTest::Unit::TestCase

  # def setup
  # end

  # def teardown
  # end

  def test_IntervalConstructor

    # fill vector with 3 days worth of hourly data
    values = OpenStudio::Vector.new(3*24, 0.000001)
    for i in (0..3*24-1)
      values[i] = i
    end

    # create timeSeries with hourly interval
    date = OpenStudio::Date.new(OpenStudio::MonthOfYear.new("Jan"), 1, 2009)
    time = OpenStudio::Time.new(0,1,0,0)
    timeSeries = OpenStudio::TimeSeries.new(date, time, values, "W")

    assert_equal(72, timeSeries.daysFromFirstReport().length())
    assert_equal(72, timeSeries.values().length())
    assert_in_delta(0.0, timeSeries.daysFromFirstReport()[0], 0.000001)
    assert_in_delta(2.0+23.0/24.0, timeSeries.daysFromFirstReport()[71], 0.000001)
  end

  def test_ValueAt

    # fill vector with 3 hours of data
    values = OpenStudio::Vector.new(3)
    for i in (0..3-1)
      values[i] = i
    end

    # create timeSeries with hourly interval
    date = OpenStudio::Date.new(OpenStudio::MonthOfYear.new("Jan"), 1, 2009)
    time = OpenStudio::Time.new(0,1,0,0)
    timeSeries = OpenStudio::TimeSeries.new(date, time, values, "W")

    assert_in_delta(0.0, timeSeries.value(OpenStudio::Time.new(0,0,0,0)), 0.000001)
    assert_in_delta(1.0, timeSeries.value(OpenStudio::Time.new(0,0,0,1)), 0.000001)
    assert_in_delta(1.0, timeSeries.value(OpenStudio::Time.new(0,0,1,0)), 0.000001)
    assert_in_delta(1.0, timeSeries.value(OpenStudio::Time.new(0,0,59,0)), 0.000001)
    assert_in_delta(1.0, timeSeries.value(OpenStudio::Time.new(0,1,0,0)), 0.000001)
    assert_in_delta(2.0, timeSeries.value(OpenStudio::Time.new(0,1,0,1)), 0.000001)
    assert_in_delta(2.0, timeSeries.value(OpenStudio::Time.new(0,1,1,0)), 0.000001)
    assert_in_delta(2.0, timeSeries.value(OpenStudio::Time.new(0,1,59,0)), 0.000001)
    assert_in_delta(2.0, timeSeries.value(OpenStudio::Time.new(0,2,0,0)), 0.000001)
  end

end


