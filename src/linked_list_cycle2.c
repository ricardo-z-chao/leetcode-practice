#include "leetcode/linked_list_cycle2.h"

#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Leetcode 142. 环形链表 II
 * @link https://leetcode.cn/problems/linked-list-cycle-ii/description/
 * @note 使用快慢指针，首先找到相遇点，然后再定义一个新的指针从链表首节点出发，
 *       与慢指针同步向前，相遇的时候即为环的入口
 * @param[in] head 链表头节点
 * @return 链表环的入口，若没有则为 NULL
 */
struct ListNode* detectCycle(struct ListNode* head) {
  struct ListNode *slow = head, *fast = head;
  while (true) {
    if (slow == NULL || slow->next == NULL) return NULL;
    if (fast == NULL || fast->next == NULL) return NULL;
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) break;
  }
  struct ListNode* ptr = head;
  while (ptr != slow) {
    ptr = ptr->next;
    slow = slow->next;
  }
  return ptr;
}
