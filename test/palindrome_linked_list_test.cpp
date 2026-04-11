extern "C" {
#include "leetcode/palindrome_linked_list.h"
}

#include <vector>

#define INCLUDE_UTILS
#ifdef INCLUDE_UTILS
  #include "utils/linked_list_utils.h"
#endif

#include "gtest/gtest.h"

struct TestParam {
  std::vector<int> head;
  bool expected;
};

class PalindromeLinkedListTest : public ::testing::TestWithParam<TestParam> {
 protected:
  struct ListNode* list;

  void TearDown() override {
    freeList(list);
  }
};

TEST_P(PalindromeLinkedListTest, Default) {
  TestParam param = GetParam();
  list = createListFromArray(param.head);
  bool result = isPalindrome(list);
  EXPECT_EQ(result, param.expected);
}

INSTANTIATE_TEST_SUITE_P(PalindromeLinkedListDataSet,
                         PalindromeLinkedListTest,
                         ::testing::Values(TestParam{{1, 2}, false}, TestParam{{1, 2, 2, 1}, true}),
                         [](const ::testing::TestParamInfo<PalindromeLinkedListTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
