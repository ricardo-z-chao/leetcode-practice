#include "leetcode/merge_two_sorted_lists.h"

#include <stdlib.h>

/**
 * @brief LeetCode 21. 合并两个有序链表
 * @link https://leetcode.cn/problems/merge-two-sorted-lists/description/
 * @param[in] list1 非递减序列
 * @param[in] list2 非递减序列
 * @return list1 和 list2 合并后的非递减序列
 */
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
  /* 这里定义一个哑节点，这样就不用处理第一次尾指针指向 NULL
   * 的情况，而在返回时直接返回链表第一个元素的指针 */
  struct ListNode* dummy = calloc(1, sizeof(struct ListNode));
  struct ListNode* tail = dummy;
  while (list1 != NULL || list2 != NULL) {
    /* 只要链表有一个已经遍历完成，直接把剩下的链表接到新链表的尾部 */
    if (list1 == NULL || list2 == NULL) {
      tail->next = list1 != NULL ? list1 : list2;
      break;
    }
    /* 每次循环时，移动较小的那个指针，然后将前一个节点加入到新链表的尾部 */
    if (list1->val <= list2->val) {
      tail->next = list1;
      list1 = list1->next;
    } else {
      tail->next = list2;
      list2 = list2->next;
    }
    tail = tail->next;
  }
  return dummy->next;
}
