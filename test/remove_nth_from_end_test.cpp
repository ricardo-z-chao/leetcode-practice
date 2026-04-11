extern "C" {
#include "leetcode/remove_nth_from_end.h"
}

#include <vector>

#define INCLUDE_UTILS
#ifdef INCLUDE_UTILS
  #include "utils/linked_list_utils.h"
#endif

#include "gtest/gtest.h"

struct TestParam {
  std::vector<int> head;
  int n;
  std::vector<int> expected;
};

class RemoveNthFromEndTest : public ::testing::TestWithParam<TestParam> {
 protected:
  struct ListNode* result;

  void TearDown() override {
    freeList(result);
  }
};

TEST_P(RemoveNthFromEndTest, Default) {
  TestParam param = GetParam();
  struct ListNode* head = createListFromArray(param.head);
  result = removeNthFromEnd(head, param.n);
  EXPECT_EQ(listToVector(result), param.expected);
}

INSTANTIATE_TEST_SUITE_P(RemoveNthFromEndDataSet,
                         RemoveNthFromEndTest,
                         ::testing::Values(TestParam{{1, 2, 3, 4, 5}, 2, {1, 2, 3, 5}},
                                           TestParam{{1}, 1, {}},
                                           TestParam{{1, 2}, 1, {1}}),
                         [](const ::testing::TestParamInfo<RemoveNthFromEndTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
