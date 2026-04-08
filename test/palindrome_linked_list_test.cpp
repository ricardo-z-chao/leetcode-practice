extern "C" {
#include "leetcode/palindrome_linked_list.h"
}

#include <vector>

#include "gtest/gtest.h"

static struct ListNode* createListFromArray(std::vector<int> arr) {
  if (arr.empty()) return NULL;
  struct ListNode* dummy = (struct ListNode*)calloc(1, sizeof(struct ListNode));
  struct ListNode* tail = dummy;
  for (const auto& value : arr) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = value;
    newNode->next = NULL;
    tail->next = newNode;
    tail = tail->next;
  }
  return dummy->next;
}

static void freeList(struct ListNode* list) {
  while (list != NULL) {
    struct ListNode* releasedNode = list;
    list = list->next;
    free(releasedNode);
  }
}

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
