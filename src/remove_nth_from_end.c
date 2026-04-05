#include "leetcode/remove_nth_from_end.h"

#include <stdlib.h>

/**
 * @brief Leetcode 19. 删除链表的倒数第 N 个结点
 * @link https://leetcode.cn/problems/remove-nth-node-from-end-of-list/description/
 * @note 这题可以使用双指针，让前后指针间隔为 N-1，然后左右指针同时向右移动，当右指针指向链表的 NULL
 *       节点时，左节点就是链表的倒数第 N 个结点
 * @param[in,out] head 链表头节点
 * @param[in] n 指定倒数第N个
 * @return 删除节点后的链表
 */
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
  struct ListNode **left = &head, **right = &head;
  /* 右节点先前进n */
  int i = 0;
  while (*right != NULL && i < n) {
    right = &((*right)->next);
    i++;
  }
  /* 判断是否提前结束循环 */
  if (i == n) {
    /* 左右节点一起前进 */
    while (*right != NULL) {
      left = &((*left)->next);
      right = &((*right)->next);
    }
    /* 删除节点 */
    struct ListNode* node = *left;
    *left = (*left)->next;
    free(node);
  }
  return head;
}
