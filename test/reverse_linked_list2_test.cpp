extern "C" {
#include "leetcode/reverse_linked_list2.h"
}

#include <vector>

#define INCLUDE_UTILS
#ifdef INCLUDE_UTILS
  #include "utils/linked_list_utils.h"
#endif

#include "gtest/gtest.h"

struct TestParam {
  std::vector<int> values;
  int left;
  int right;
  std::vector<int> expected;
};

class ReverseLinkedList2Test : public ::testing::TestWithParam<TestParam> {
 protected:
  struct ListNode* result;

  void TearDown() override {
    freeList(result);
  }
};

TEST_P(ReverseLinkedList2Test, Default) {
  TestParam param = GetParam();
  struct ListNode* head = createListFromArray(param.values);
  result = reverseBetween(head, param.left, param.right);
  EXPECT_EQ(listToVector(result), param.expected);
}

INSTANTIATE_TEST_SUITE_P(ReverseLinkedList2DataSet,
                         ReverseLinkedList2Test,
                         ::testing::Values(TestParam{{1, 2, 3, 4, 5}, 2, 4, {1, 4, 3, 2, 5}},
                                           TestParam{{5}, 1, 1, {5}}),
                         [](const ::testing::TestParamInfo<ReverseLinkedList2Test::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
