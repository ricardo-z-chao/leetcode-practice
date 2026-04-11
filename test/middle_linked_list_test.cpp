extern "C" {
#include "leetcode/middle_linked_list.h"
}

#include <vector>

#define INCLUDE_UTILS
#ifdef INCLUDE_UTILS
  #include "utils/linked_list_utils.h"
#endif

#include "gtest/gtest.h"

struct TestParam {
  std::vector<int> head;
  int expected;
};

class MiddleLinkedListTest : public ::testing::TestWithParam<TestParam> {
 protected:
  struct ListNode* list;

  void TearDown() override {
    freeList(list);
  }
};

TEST_P(MiddleLinkedListTest, Default) {
  TestParam param = GetParam();
  list = createListFromArray(param.head);
  struct ListNode* result = middleNode(list);
  EXPECT_EQ(result->val, param.expected);
}

INSTANTIATE_TEST_SUITE_P(MiddleLinkedListDataSet,
                         MiddleLinkedListTest,
                         ::testing::Values(TestParam{{1, 2, 3, 4, 5}, 3}, TestParam{{1, 2, 3, 4, 5, 6}, 4}),
                         [](const ::testing::TestParamInfo<MiddleLinkedListTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
