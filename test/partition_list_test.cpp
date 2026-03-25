extern "C" {
#include "leetcode/partition_list.h"
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
  std::vector<int> input;
  int x;
  std::vector<int> expected;
};

class PartitionListTest : public ::testing::TestWithParam<TestParam> {
 protected:
  struct ListNode* result;

  void TearDown() override {
    freeList(result);
  }
};

TEST_P(PartitionListTest, Default) {
  TestParam param = GetParam();
  struct ListNode* inputList = createListFromArray(param.input);
  result = partition(inputList, param.x);
  EXPECT_EQ(listToVector(result), param.expected);
}

INSTANTIATE_TEST_SUITE_P(PartitionListTestDataSet,
                         PartitionListTest,
                         ::testing::Values(TestParam{{1, 4, 3, 2, 5, 2}, 3, {1, 2, 2, 4, 3, 5}},
                                           TestParam{{2, 1}, 2, {1, 2}}),
                         [](const ::testing::TestParamInfo<PartitionListTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
