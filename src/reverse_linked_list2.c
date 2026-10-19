#include "leetcode/reverse_linked_list2.h"

#include <stdlib.h>

/**
 * @brief Leetcode 92. 反转链表 II
 * @link https://leetcode.cn/problems/reverse-linked-list-ii/description/
 * @note 通常情况下，我们思考是将left指向的节点插入到right节点之后，然后left前进一步，
 *       当left和right重合时这个循环就结束了，链表就反转完成了，但是这里是给定了两个整数，
 *       这种办法要遍历两遍链表，第一遍用来确定left和right指针，第二遍才开始反转。
 *       有没有遍历一遍就能解决的方法？我们可以先确定left节点的前一个节点prev，将left当作反转部分的尾节点tail，
 *       然后依次遍历节点将节点加入到prev之后，然后最后将剩下的节点加入到tail之后。
 * @param[in] head 链表头节点
 * @param[in] left 指定范围开始
 * @param[in] right 指定范围结束
 * @return 反转后的链表
 */
struct ListNode* reverseBetween(struct ListNode* head, int left, int right) {
  struct ListNode* dummy = malloc(sizeof(struct ListNode));
  dummy->next = head;
  struct ListNode* prev = dummy;
  int i = 0;
  /* 初始化prev指针 */
  while (i < left - 1 && prev != NULL) {
    prev = prev->next;
    i++;
  }
  if (prev != NULL) {
    struct ListNode *cur = prev->next, *tail = prev->next;
    while (i < right && cur != NULL) {
      struct ListNode* next = prev->next;
      prev->next = cur;
      cur = cur->next;
      prev->next->next = next;
      i++;
    }
    tail->next = cur;
  }
  return dummy->next;
}
