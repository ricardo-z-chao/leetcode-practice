extern "C" {
#include "leetcode/partition_list.h"
}

#include <vector>

#define INCLUDE_UTILS
#ifdef INCLUDE_UTILS
  #include "utils/linked_list_utils.h"
#endif

#include "gtest/gtest.h"

struct TestParam {
  std::vector<int> input;
  int x;
  std::vector<int> expected;
};

class PartitionListTest : public ::testing::TestWithParam<TestParam> {
 protected:
  struct ListNode* result;

  void TearDown() override {
    freeList(result);
  }
};

TEST_P(PartitionListTest, Default) {
  TestParam param = GetParam();
  struct ListNode* inputList = createListFromArray(param.input);
  result = partition(inputList, param.x);
  EXPECT_EQ(listToVector(result), param.expected);
}

INSTANTIATE_TEST_SUITE_P(PartitionListTestDataSet,
                         PartitionListTest,
                         ::testing::Values(TestParam{{1, 4, 3, 2, 5, 2}, 3, {1, 2, 2, 4, 3, 5}},
                                           TestParam{{2, 1}, 2, {1, 2}}),
                         [](const ::testing::TestParamInfo<PartitionListTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
