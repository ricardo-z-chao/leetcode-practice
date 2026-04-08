#include "leetcode/palindrome_linked_list.h"

#include <stdlib.h>

static struct ListNode* reverse(struct ListNode*);

/**
 * @brief Leetcode 234. 回文链表
 * @link https://leetcode.cn/problems/palindrome-linked-list/
 * @param[in] head 链表头节点
 * @return true表示是回文链表，false表示不是回文链表
 */
bool isPalindrome(struct ListNode* head) {
  struct ListNode* dummy = malloc(sizeof(struct ListNode));
  dummy->next = head;
  /* 查找中间节点 */
  struct ListNode *slow = dummy, *fast = dummy;
  while (fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
  }
  /* 从中间节点的一下节点开始反转链表 */
  struct ListNode* start = slow->next;
  struct ListNode* pre = NULL;
  for (struct ListNode* cur = start; cur != NULL; cur = start) {
    start = start->next;
    cur->next = pre;
    pre = cur;
  }
  slow->next = pre;
  /* 比较直到指向中间节点结束 */
  for (struct ListNode* i = head; pre != NULL && i <= slow; i = i->next, pre = pre->next) {
    if (i->val != pre->val) {
      return false;
    }
  }
  return true;
}
