extern "C" {
#include "leetcode/trapping_rain_water.h"
}

#include <vector>

#include "gtest/gtest.h"

struct TestParam {
  std::vector<int> height;
  int expected;
};

class TrappingRainWaterTest : public ::testing::TestWithParam<TestParam> {
 protected:
  TestParam param = GetParam();

  void SetUp() override {}

  void TearDown() override {}
};

TEST_P(TrappingRainWaterTest, Default) {
  int result = trap(param.height.data(), param.height.size());
  EXPECT_EQ(result, param.expected);
}

INSTANTIATE_TEST_SUITE_P(TrappingRainWaterDataSet,
                         TrappingRainWaterTest,
                         ::testing::Values(TestParam{{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}, 6},
                                           TestParam{{4, 2, 0, 3, 2, 5}, 9}),
                         [](const ::testing::TestParamInfo<TrappingRainWaterTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
