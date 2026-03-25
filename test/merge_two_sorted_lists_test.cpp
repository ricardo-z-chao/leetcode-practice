extern "C" {
#include "leetcode/merge_two_sorted_lists.h"
}

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

static std::vector<int> listToVector(struct ListNode* list) {
  std::vector<int> result;
  while (list != NULL) {
    result.push_back(list->val);
    list = list->next;
  }
  return result;
}

static void freeList(struct ListNode* list) {
  while (list != NULL) {
    struct ListNode* temp = list;
    list = list->next;
    free(temp);
  }
}

TEST(MergeTwoSortedListsTest, Case1) {
  std::vector<int> l1 = {1, 2, 4};
  std::vector<int> l2 = {1, 3, 4};
  std::vector<int> expected = {1, 1, 2, 3, 4, 4};

  struct ListNode* list1 = createListFromArray(l1);
  struct ListNode* list2 = createListFromArray(l2);

  struct ListNode* result = mergeTwoLists(list1, list2);
  std::vector<int> actual = listToVector(result);

  EXPECT_EQ(actual.size(), expected.size());
  for (size_t i = 0; i < expected.size(); i++) {
    EXPECT_EQ(actual[i], expected[i]);
  }

  freeList(result);
}
