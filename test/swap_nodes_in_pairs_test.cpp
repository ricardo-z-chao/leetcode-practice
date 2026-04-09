extern "C" {
#include "leetcode/swap_nodes_in_pairs.h"
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
  std::vector<int> expected;
};

class SwapNodesInPairsTest : public ::testing::TestWithParam<TestParam> {
 protected:
  struct ListNode* head;

  void SetUp() override {
    TestParam param = GetParam();
    head = createListFromArray(param.values);
  }

  void TearDown() override {}
};

TEST_P(SwapNodesInPairsTest, Default) {
  TestParam param = GetParam();
  struct ListNode* result = swapPairs(head);
  std::vector<int> resultVec = listToVector(result);
  EXPECT_EQ(resultVec, param.expected);
  freeList(result);
}

INSTANTIATE_TEST_SUITE_P(SwapNodesInPairsDataSet,
                         SwapNodesInPairsTest,
                         ::testing::Values(TestParam{{1, 2, 3, 4}, {2, 1, 4, 3}}, TestParam{{}, {}}),
                         [](const ::testing::TestParamInfo<SwapNodesInPairsTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
