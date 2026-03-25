extern "C" {
#include "leetcode/partition_list.h"
}

#include <cstddef>
#include <vector>

#include "gtest/gtest.h"

static struct ListNode* createListFromArray(std::vector<int> arr) {
  if (arr.empty()) return NULL;

  struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
  head->val = arr[0];
  head->next = NULL;

  struct ListNode* current = head;
  for (size_t i = 1; i < arr.size(); i++) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = arr[i];
    newNode->next = NULL;
    current->next = newNode;
    current = current->next;
  }

  return head;
}

static void freeList(struct ListNode* list) {
  while (list != NULL) {
    struct ListNode* temp = list;
    list = list->next;
    free(temp);
  }
}

static void expectListEqualsArray(struct ListNode* list, std::vector<int> expected) {
  struct ListNode* current = list;
  for (size_t i = 0; i < expected.size(); i++) {
    ASSERT_NE(current, nullptr);
    EXPECT_EQ(current->val, expected[i]);
    current = current->next;
  }
  ASSERT_EQ(current, nullptr);
}

class PartitionListTest : public ::testing::Test {
 protected:
  void TearDown() override {}
};

TEST_F(PartitionListTest, Case1) {
  std::vector<int> input = {1, 4, 3, 2, 5, 2};
  std::vector<int> expected = {1, 2, 2, 4, 3, 5};
  int x = 3;

  struct ListNode* head = createListFromArray(input);
  struct ListNode* result = partition(head, x);

  expectListEqualsArray(result, expected);

  freeList(result);
}

TEST_F(PartitionListTest, Case2) {
  std::vector<int> input = {2, 1};
  std::vector<int> expected = {1, 2};
  int x = 2;

  struct ListNode* head = createListFromArray(input);
  struct ListNode* result = partition(head, x);

  expectListEqualsArray(result, expected);

  freeList(result);
}
