#include "leetcode/partition_list.h"

#include <stdlib.h>

/**
 * @brief LeetCode 86. 分隔链表
 * @link https://leetcode.cn/problems/partition-list/description/
 * @note 注意到这里的 dummy->next = head，这里直接把哑节点直接指向链表是因为考虑到边界情况，
 *       如果链表的第一个节点就是大于等于 x 的节点（测试用例 Case2），当 for 循环中的初始值是
 *       struct ListNode** current = &head 这种写法，这样哑节点就不能正确指向调整后的节点
 * @param[in,out] head 头节点指针
 * @param[in] x 指定的值
 * @return 新的链表
 */
struct ListNode* partition(struct ListNode* head, int x) {
  struct ListNode* dummy = calloc(1, sizeof(struct ListNode));
  dummy->next = head;
  struct ListNode* tail = dummy;
  struct ListNode** first = NULL;
  for (struct ListNode** current = &dummy->next; *current != NULL;) {
    /* 查找第一个大于等于x的节点 */
    if (first == NULL && (*current)->val >= x) {
      first = current;
    }
    /* 如果已经有第一个大于等于x的节点，并且当前节点小于这个节点就把当前节点放到到这个节点之前 */
    if (first != NULL && (*current)->val < x) {
      struct ListNode* node = *current;
      *current = (*current)->next;
      node->next = *first;
      *first = node;
      first = &(*first)->next;
      continue;
    }
    tail->next = *current;
    tail = tail->next;
    current = &(*current)->next;
  }
  return dummy->next;
}
