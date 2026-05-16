extern "C" {
#include "leetcode/range_addition.h"
}

#include <stdlib.h>

#include <vector>

#include "gtest/gtest.h"

struct TestParam {
  int length;
  std::vector<std::vector<int>> updates;
  std::vector<int> expected;
};

class RangeAdditionTest : public ::testing::TestWithParam<TestParam> {
 protected:
  TestParam param = GetParam();
  int** updates;
  int* result;

  void SetUp() override {
    updates = reinterpret_cast<int**>(malloc(param.updates.size() * sizeof(int*)));
    for (size_t i = 0; i < 3; i++) {
      updates[i] = reinterpret_cast<int*>(malloc(3 * sizeof(int)));
      updates[i][0] = param.updates[i][0];
      updates[i][1] = param.updates[i][1];
      updates[i][2] = param.updates[i][2];
    }
  }

  void TearDown() override {}
};

TEST_P(RangeAdditionTest, Default) {
  int returnSize;
  int* result = getModifiedArray(param.length, updates, param.updates.size(), NULL, &returnSize);
  for (int i = 0; i < returnSize; ++i) {
    ASSERT_EQ(result[i], param.expected[i]);
  }
}

INSTANTIATE_TEST_SUITE_P(RangeAdditionDataSet,
                         RangeAdditionTest,
                         ::testing::Values(TestParam{5, {{1, 3, 2}, {2, 4, 3}, {0, 2, -2}}, {-2, 0, 3, 5, 3}}),
                         [](const ::testing::TestParamInfo<RangeAdditionTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
