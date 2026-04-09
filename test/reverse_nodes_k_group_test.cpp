extern "C" {
#include "leetcode/reverse_nodes_k_group.h"
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
  int k;
  std::vector<int> expected;
};

class ReverseNodesKGroupTest : public ::testing::TestWithParam<TestParam> {
 protected:
  struct ListNode* head;

  void SetUp() override {
    TestParam param = GetParam();
    head = createListFromArray(param.values);
  }

  void TearDown() override {}
};

TEST_P(ReverseNodesKGroupTest, Default) {
  TestParam param = GetParam();
  struct ListNode* result = reverseKGroup(head, param.k);
  std::vector<int> resultVec = listToVector(result);
  EXPECT_EQ(resultVec, param.expected);
  freeList(result);
}

INSTANTIATE_TEST_SUITE_P(ReverseNodesKGroupDataSet,
                         ReverseNodesKGroupTest,
                         ::testing::Values(TestParam{{1, 2, 3, 4, 5}, 2, {2, 1, 4, 3, 5}},
                                           TestParam{{1, 2, 3, 4, 5}, 3, {3, 2, 1, 4, 5}}),
                         [](const ::testing::TestParamInfo<ReverseNodesKGroupTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
