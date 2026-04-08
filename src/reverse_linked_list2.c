#include "leetcode/reverse_linked_list2.h"

#include <stdlib.h>

/**
 * @brief Leetcode 92. 反转链表 II
 * @link https://leetcode.cn/problems/reverse-linked-list-ii/description/
 * @param[in] head 链表头节点
 * @param[in] left 指定范围开始
 * @param[in] right 指定范围结束
 * @return 反转后的链表
 */
struct ListNode* reverseBetween(struct ListNode* head, int left, int right) {
  struct ListNode* dummy = malloc(sizeof(struct ListNode));
  dummy->next = head;
  struct ListNode** pre = &(dummy->next);
  /* 将pre指针移动到left节点的前一个节点 */
  int i = 0;
  while (i < left - 1 && (*pre) != NULL) {
    pre = &(*pre)->next;
    i++;
  }
  if (i == left - 1) {
    struct ListNode *tail = *pre, *cur = *pre;
    while (i < right && cur != NULL) {
      struct ListNode* node = *pre;
      *pre = cur;
      cur = cur->next;
      (*pre)->next = node;
      i++;
    }
    tail->next = cur;
  }
  return dummy->next;
}
