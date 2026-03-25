extern "C" {
#include "leetcode/merge_two_sorted_lists.h"
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
  std::vector<int> l1;
  std::vector<int> l2;
  std::vector<int> expected;
};

class MergeTwoSortedListsTest : public ::testing::TestWithParam<TestParam> {
 protected:
  struct ListNode* result;

  void TearDown() override {
    freeList(result);
  }
};


TEST_P(MergeTwoSortedListsTest, Default) {
  TestParam param = GetParam();
  struct ListNode* list1 = createListFromArray(param.l1);
  struct ListNode* list2 = createListFromArray(param.l2);
  result = mergeTwoLists(list1, list2);
  EXPECT_EQ(listToVector(result), param.expected);
}

INSTANTIATE_TEST_SUITE_P(MergeTwoSortedListsDataSet,
                         MergeTwoSortedListsTest,
                         ::testing::Values(TestParam{{1, 2, 4}, {1, 3, 4}, {1, 1, 2, 3, 4, 4}}),
                         [](const ::testing::TestParamInfo<MergeTwoSortedListsTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
