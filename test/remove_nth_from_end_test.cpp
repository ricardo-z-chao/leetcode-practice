extern "C" {
#include "leetcode/remove_nth_from_end.h"
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

static std::vector<int> listToVector(struct ListNode* list) {
  std::vector<int> result;
  while (list != nullptr) {
    result.push_back(list->val);
    list = list->next;
  }
  return result;
}

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
