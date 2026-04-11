extern "C" {
#include "leetcode/linked_list_cycle2.h"
}

#include <vector>

#define INCLUDE_UTILS
#ifdef INCLUDE_UTILS
  #include "utils/linked_list_utils.h"
#endif

#include "gtest/gtest.h"

struct TestParam {
  std::vector<int> values;
  int pos;  // -1 means no cycle, otherwise index of node where cycle begins
  int expectedCycleNodeVal;  // value at the cycle start node
};

class LinkedListCycle2Test : public ::testing::TestWithParam<TestParam> {
 protected:
  struct ListNode* head;

  void SetUp() override {
    TestParam param = GetParam();
    head = createListFromArray(param.values);

    if (param.pos != -1) {
      // Create cycle: node at pos points back to itself (or to head to form cycle)
      struct ListNode* targetNode = head;
      for (int i = 0; i < param.pos; i++) {
        targetNode = targetNode->next;
      }
      // Find the last node and point it to targetNode
      struct ListNode* current = head;
      while (current->next != NULL) {
        current = current->next;
      }
      current->next = targetNode;
    }
  }

  void TearDown() override {
    // If list has a cycle, we can't use freeList as it will infinite loop
    // For test cleanup, we rely on process exit to reclaim memory
    TestParam param = GetParam();
    if (param.pos == -1) {
      freeList(head);
    }
    // When there's a cycle, don't free - would cause infinite traversal
  }
};

TEST_P(LinkedListCycle2Test, Default) {
  TestParam param = GetParam();
  struct ListNode* result = detectCycle(head);
  if (param.pos == -1) {
    EXPECT_EQ(result, nullptr);
  } else {
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->val, param.expectedCycleNodeVal);
  }
}

INSTANTIATE_TEST_SUITE_P(LinkedListCycle2DataSet,
                         LinkedListCycle2Test,
                         ::testing::Values(TestParam{{3, 2, 0, -4}, 1, 2}, TestParam{{1, 2}, 0, 1}),
                         [](const ::testing::TestParamInfo<LinkedListCycle2Test::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
