extern "C" {
#include "leetcode/reverse_nodes_k_group.h"
}

#include <vector>

#define INCLUDE_UTILS
#ifdef INCLUDE_UTILS
  #include "utils/linked_list_utils.h"
#endif

#include "gtest/gtest.h"

struct TestParam {
  std::vector<int> values;
  int k;
  std::vector<int> expected;
};

class ReverseNodesKGroupTest : public ::testing::TestWithParam<TestParam> {
 protected:
  struct ListNode* head;

  void SetUp() override {
    TestParam param = GetParam();
    head = createListFromArray(param.values);
  }

  void TearDown() override {}
};

TEST_P(ReverseNodesKGroupTest, Default) {
  TestParam param = GetParam();
  struct ListNode* result = reverseKGroup(head, param.k);
  std::vector<int> resultVec = listToVector(result);
  EXPECT_EQ(resultVec, param.expected);
  freeList(result);
}

INSTANTIATE_TEST_SUITE_P(ReverseNodesKGroupDataSet,
                         ReverseNodesKGroupTest,
                         ::testing::Values(TestParam{{1, 2, 3, 4, 5}, 2, {2, 1, 4, 3, 5}},
                                           TestParam{{1, 2, 3, 4, 5}, 3, {3, 2, 1, 4, 5}}),
                         [](const ::testing::TestParamInfo<ReverseNodesKGroupTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
