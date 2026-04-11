extern "C" {
#include "leetcode/swap_nodes_in_pairs.h"
}

#include <vector>

#define INCLUDE_UTILS
#ifdef INCLUDE_UTILS
  #include "utils/linked_list_utils.h"
#endif

#include "gtest/gtest.h"

struct TestParam {
  std::vector<int> values;
  std::vector<int> expected;
};

class SwapNodesInPairsTest : public ::testing::TestWithParam<TestParam> {
 protected:
  struct ListNode* head;

  void SetUp() override {
    TestParam param = GetParam();
    head = createListFromArray(param.values);
  }

  void TearDown() override {}
};

TEST_P(SwapNodesInPairsTest, Default) {
  TestParam param = GetParam();
  struct ListNode* result = swapPairs(head);
  std::vector<int> resultVec = listToVector(result);
  EXPECT_EQ(resultVec, param.expected);
  freeList(result);
}

INSTANTIATE_TEST_SUITE_P(SwapNodesInPairsDataSet,
                         SwapNodesInPairsTest,
                         ::testing::Values(TestParam{{1, 2, 3, 4}, {2, 1, 4, 3}}, TestParam{{}, {}}),
                         [](const ::testing::TestParamInfo<SwapNodesInPairsTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
