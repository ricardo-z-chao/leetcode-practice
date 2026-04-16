extern "C" {
#include "leetcode/sort_an_array.h"
}

#include <vector>

#include "gtest/gtest.h"

struct TestParam {
  std::vector<int> input;
  std::vector<int> expected;
};

class SortAnArrayTest : public ::testing::TestWithParam<TestParam> {
 protected:
  int* result = NULL;
  int returnSize = 0;
};

TEST_P(SortAnArrayTest, Default) {
  TestParam param = GetParam();
  result = sortArray(param.input.data(), param.input.size(), &returnSize);
  ASSERT_EQ(returnSize, param.expected.size());
  for (int i = 0; i < returnSize; i++) {
    EXPECT_EQ(result[i], param.expected[i]);
  }
}

INSTANTIATE_TEST_SUITE_P(SortAnArrayDataSet,
                         SortAnArrayTest,
                         ::testing::Values(TestParam{{5, 1, 1, 2, 0, 0}, {0, 0, 1, 1, 2, 5}}),
                         [](const ::testing::TestParamInfo<SortAnArrayTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
