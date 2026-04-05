extern "C" {
#include "leetcode/middle_linked_list.h"
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
