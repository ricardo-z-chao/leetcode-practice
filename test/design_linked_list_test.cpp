extern "C" {
#include "leetcode/design_linked_list.h"
}

#include "gtest/gtest.h"

class DesignLinkedListTest : public ::testing::Test {
 protected:
  MyLinkedList* list = nullptr;

  void SetUp() override { list = myLinkedListCreate(); }

  void TearDown() override { myLinkedListFree(list); }
};

TEST_F(DesignLinkedListTest, Case1) {
  myLinkedListAddAtHead(list, 1);          // 链表：1
  myLinkedListAddAtTail(list, 3);          // 链表：1->3
  myLinkedListAddAtIndex(list, 1, 2);      // 链表：1->2->3
  EXPECT_EQ(myLinkedListGet(list, 1), 2);  // 返回 2
  myLinkedListDeleteAtIndex(list, 1);      // 链表：1->3
  EXPECT_EQ(myLinkedListGet(list, 1), 3);  // 返回 3
}

TEST_F(DesignLinkedListTest, Case2) {
  myLinkedListAddAtHead(list, 7);          // 链表：7
  myLinkedListAddAtHead(list, 2);          // 链表：2->7
  myLinkedListAddAtHead(list, 1);          // 链表：1->2->7
  myLinkedListAddAtIndex(list, 3, 0);      // 链表：1->2->7->0
  myLinkedListDeleteAtIndex(list, 2);      // 链表：1->2->0
  myLinkedListAddAtHead(list, 6);          // 链表：6->1->2->0
  myLinkedListAddAtTail(list, 4);          // 链表：6->1->2->0->4
  EXPECT_EQ(myLinkedListGet(list, 4), 4);  // 返回 4
  myLinkedListAddAtHead(list, 4);          // 链表：4->6->1->2->0->4
  myLinkedListAddAtIndex(list, 5, 0);      // 链表：4->6->1->2->0->0->4
  myLinkedListAddAtHead(list, 6);          // 链表：6->4->6->1->2->0->0->4
}

TEST_F(DesignLinkedListTest, Case3) {
  myLinkedListAddAtTail(list, 1);          // 链表：1
  EXPECT_EQ(myLinkedListGet(list, 0), 1);  // 返回 1
}
