extern "C" {
#include "leetcode/merge_k_sorted_lists.h"
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
  std::vector<std::vector<int>> lists;
  std::vector<int> expected;
};

class MergeKSortedListsTest : public ::testing::TestWithParam<TestParam> {
 protected:
  struct ListNode* result;

  void TearDown() override {
    freeList(result);
  }
};

TEST_P(MergeKSortedListsTest, Default) {
  TestParam param = GetParam();
  int k = param.lists.size();
  struct ListNode** lists = (struct ListNode**)malloc(k * sizeof(struct ListNode*));
  for (int i = 0; i < k; i++) {
    lists[i] = createListFromArray(param.lists[i]);
  }
  result = mergeKLists(lists, k);
  EXPECT_EQ(listToVector(result), param.expected);
}

INSTANTIATE_TEST_SUITE_P(MergeKSortedListsDataSet,
                         MergeKSortedListsTest,
                         ::testing::Values(TestParam{{{1, 4, 5}, {1, 3, 4}, {2, 6}}, {1, 1, 2, 3, 4, 4, 5, 6}}),
                         [](const ::testing::TestParamInfo<MergeKSortedListsTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
