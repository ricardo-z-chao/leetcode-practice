#include "leetcode/intersection_two_linked_lists.h"

#include <stdlib.h>

/**
 * @brief Leetcode 160.相交链表
 * @link https://leetcode.cn/problems/intersection-of-two-linked-lists/description/
 * @note 假设链表 A 为：a + m，链表 B 为：b + m，其中 m 是公共部分。
 *       让 p 指针遍历链表 A，q 指针遍历链表 B，当遍历到链表尾时，再从另一个链表头继续遍历，当指针 p 和 q
 *       相遇时，就是链表的相交部分。
 *       A: a + m + b
 *       B: b + m + a
 * @param[in] headA 链表A头节点
 * @param[in] headB 链表B头节点
 * @return 相交的节点，如果没有则返回 NULL
 */
struct ListNode* getIntersectionNode(struct ListNode* headA, struct ListNode* headB) {
  struct ListNode *p = headA, *q = headB;
  while (p != q) {
    p = p == NULL ? headB : p->next;
    q = q == NULL ? headA : q->next;
  }
  return p;
}
