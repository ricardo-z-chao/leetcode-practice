#include "leetcode/swap_nodes_in_pairs.h"

#include <stdlib.h>

/**
 * @brief Leetcode 24. 两两交换链表中的节点
 * @link https://leetcode.cn/problems/swap-nodes-in-pairs/
 * @param[in] head 链表头节点
 * @return 交换节点后的链表
 */
struct ListNode* swapPairs(struct ListNode* head) {
  if (head == NULL || head->next == NULL) return head;
  struct ListNode* first = head;
  struct ListNode* second = head->next;
  first->next = swapPairs(second->next);
  second->next = first;
  return second;
}
