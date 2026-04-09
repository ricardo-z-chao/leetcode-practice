#include "leetcode/reverse_nodes_k_group.h"

#include <stdlib.h>

/**
 * @brief Leetcode 25. K 个一组翻转链表
 * @link https://leetcode.cn/problems/reverse-nodes-in-k-group/description/
 * @param[in] head 链表头节点
 * @param k 整数
 * @return 翻转后的链表
 */
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
  /* 判断是否满足k个 */
  int i = 0;
  struct ListNode* node = head;
  while (node != NULL && i < k) {
    node = node->next;
    i++;
  }
  if (i < k) return head;
  /* 反转数组 */
  struct ListNode *pre = node, *tail = head;
  i = 0;
  for (struct ListNode* cur = head; i < k; i++, cur = head) {
    head = head->next;
    cur->next = pre;
    pre = cur;
  }
  tail->next = reverseKGroup(node, k);
  return pre;
}
