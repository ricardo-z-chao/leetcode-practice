extern "C" {
#include "leetcode/intersection_two_linked_lists.h"
}

#include <vector>

#define INCLUDE_UTILS
#ifdef INCLUDE_UTILS
  #include "utils/linked_list_utils.h"
#endif

#include "gtest/gtest.h"

static struct ListNode* createIntersectingLists(std::vector<int> listA,
                                                std::vector<int> listB,
                                                std::vector<int> intersect) {
  // Create listA: listA + intersect
  // Create listB: listB + intersect (shares the same intersect nodes)
  struct ListNode* dummyA = (struct ListNode*)calloc(1, sizeof(struct ListNode));
  struct ListNode* tailA = dummyA;
  for (const auto& val : listA) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    tailA->next = newNode;
    tailA = tailA->next;
  }

  struct ListNode* dummyB = (struct ListNode*)calloc(1, sizeof(struct ListNode));
  struct ListNode* tailB = dummyB;
  for (const auto& val : listB) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    tailB->next = newNode;
    tailB = tailB->next;
  }

  // Build intersect nodes
  struct ListNode* dummyIntersect = (struct ListNode*)calloc(1, sizeof(struct ListNode));
  struct ListNode* tailIntersect = dummyIntersect;
  for (const auto& val : intersect) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    tailIntersect->next = newNode;
    tailIntersect = tailIntersect->next;
  }

  // Connect both lists to intersect
  tailA->next = dummyIntersect->next;
  tailB->next = dummyIntersect->next;

  struct ListNode* headA = dummyA->next;
  struct ListNode* headB = dummyB->next;

  free(dummyA);
  free(dummyB);
  free(dummyIntersect);

  // Return headA in result, but caller should use headA and headB
  return headA;
}

struct TestParam {
  std::vector<int> listA;
  std::vector<int> listB;
  std::vector<int> intersect;
  int intersectVal;
};

class IntersectionTwoLinkedListsTest : public ::testing::TestWithParam<TestParam> {
 protected:
  struct ListNode* headA;
  struct ListNode* headB;
  struct ListNode* result;

  void SetUp() override {
    TestParam param = GetParam();
    struct ListNode* dummyA = (struct ListNode*)calloc(1, sizeof(struct ListNode));
    struct ListNode* dummyB = (struct ListNode*)calloc(1, sizeof(struct ListNode));
    struct ListNode* tailA = dummyA;
    struct ListNode* tailB = dummyB;

    for (const auto& val : param.listA) {
      struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
      newNode->val = val;
      newNode->next = NULL;
      tailA->next = newNode;
      tailA = tailA->next;
    }

    for (const auto& val : param.listB) {
      struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
      newNode->val = val;
      newNode->next = NULL;
      tailB->next = newNode;
      tailB = tailB->next;
    }

    // Build intersect nodes (shared)
    struct ListNode* dummyIntersect = (struct ListNode*)calloc(1, sizeof(struct ListNode));
    struct ListNode* tailIntersect = dummyIntersect;
    for (const auto& val : param.intersect) {
      struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
      newNode->val = val;
      newNode->next = NULL;
      tailIntersect->next = newNode;
      tailIntersect = tailIntersect->next;
    }

    // Connect both tails to intersect
    tailA->next = dummyIntersect->next;
    tailB->next = dummyIntersect->next;

    headA = dummyA->next;
    headB = dummyB->next;

    free(dummyA);
    free(dummyB);
    free(dummyIntersect);
  }

  void TearDown() override {
    // Only free from headA since headB shares the same nodes
    freeList(headA);
  }
};

TEST_P(IntersectionTwoLinkedListsTest, Default) {
  TestParam param = GetParam();
  result = getIntersectionNode(headA, headB);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->val, param.intersectVal);
}

INSTANTIATE_TEST_SUITE_P(IntersectionTwoLinkedListsDataSet,
                         IntersectionTwoLinkedListsTest,
                         ::testing::Values(TestParam{{4, 1}, {5, 6, 1}, {8, 4, 5}, 8}),
                         [](const ::testing::TestParamInfo<IntersectionTwoLinkedListsTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
