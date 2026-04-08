extern "C" {
#include "leetcode/reverse_linked_list2.h"
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
