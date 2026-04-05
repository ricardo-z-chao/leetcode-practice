#include "leetcode/middle_linked_list.h"

#include <stdlib.h>

/**
 * @brief Leetcode 876. 链表的中间结点
 * @link https://leetcode.cn/problems/middle-of-the-linked-list/description/
 * @note 使用快慢指针，慢指针每次前进1，快指针每次前进2，当快指针到链表尾时，慢指针就是链表的中间节点
 * @param[in] head 链表头节点
 * @return 链表的中间节点
 */
struct ListNode* middleNode(struct ListNode* head) {
  struct ListNode *left = head, *right = head;
  while (right != NULL && right->next != NULL) {
    /*左指针前进1 */
    left = left->next;
    /* 右指针前进2 */
    right = right->next->next;
  }
  return left;
}
