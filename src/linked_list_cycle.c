#include "leetcode/linked_list_cycle.h"

#include <stdlib.h>

/**
 * @brief Leetcode 141. 环形链表
 * @link https://leetcode.cn/problems/linked-list-cycle/description/
 * @param[in] head 链表头节点
 * @return true 表示有环，false 表示没有
 */
bool hasCycle(struct ListNode* head) {
  struct ListNode *slow = head, *fast = head;
  while (true) {
    if (slow == NULL || slow->next == NULL) break;
    if (fast == NULL || fast->next == NULL) break;
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) return true;
  }
  return false;
}
