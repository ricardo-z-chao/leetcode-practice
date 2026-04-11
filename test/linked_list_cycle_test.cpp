extern "C" {
#include "leetcode/linked_list_cycle.h"
}

#include <vector>

#define INCLUDE_UTILS
#ifdef INCLUDE_UTILS
  #include "utils/linked_list_utils.h"
#endif

#include "gtest/gtest.h"

struct TestParam {
  std::vector<int> values;
  int pos;  // -1 means no cycle, otherwise index of node to point back to head
  bool expected;
};

class LinkedListCycleTest : public ::testing::TestWithParam<TestParam> {
 protected:
  struct ListNode* head;

  void SetUp() override {
    TestParam param = GetParam();
    head = createListFromArray(param.values);

    if (param.pos != -1) {
      // Create cycle: node at pos points to head
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

TEST_P(LinkedListCycleTest, Default) {
  TestParam param = GetParam();
  bool result = hasCycle(head);
  EXPECT_EQ(result, param.expected);
}

INSTANTIATE_TEST_SUITE_P(LinkedListCycleDataSet,
                         LinkedListCycleTest,
                         ::testing::Values(TestParam{{3, 2, 0, -4}, 1, true}),
                         [](const ::testing::TestParamInfo<LinkedListCycleTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
