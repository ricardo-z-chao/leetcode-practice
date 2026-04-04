#include "leetcode/merge_k_sorted_lists.h"

#include <stdlib.h>
#include <stdint.h>

static struct ListNode* solutionOne(struct ListNode**, int, int);
static struct ListNode* solutionTwo(struct ListNode**, int);
static void offer(struct ListNode**, int*, struct ListNode*);
static struct ListNode* pop(struct ListNode**, int*);

/**
 * @brief LeetCode 23. 合并 K 个升序链表
 * @link https://leetcode.cn/problems/merge-k-sorted-lists/description/
 * @param[in] lists 一个数组，其中的元素是链表的头节点
 * @param[in] listsSize 数组大小
 * @return 合并后的升序链表
 */
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
  // return solutionOne(lists, 0, listsSize - 1);
  return solutionTwo(lists, listsSize);
}

/**
 * @brief 解法一：递归
 * @note 将 k 个链表合并转化为 k/2 个链表合并的小问题，比方说我们有 10 个链表，我们先将问题
 *       转化为 5 个链表和 5 个链表合并，然后再将合并好的这两个链表再次合并就会得到最终的结果
 * @param[in] left 索引起点
 * @param[in] right 索引终点
 * @return 合并后的升序链表
 */
static struct ListNode* solutionOne(struct ListNode** lists, int left, int right) {
  if (left == right) {
    return lists[left];
  }
  if (left > right) {
    return NULL;
  }
  int mid = (left + right) >> 1;
  struct ListNode* listOne = solutionOne(lists, left, mid);
  struct ListNode* listTwo = solutionOne(lists, mid + 1, right);
  if (listOne == NULL || listTwo == NULL) {
    return listOne != NULL ? listOne : listTwo;
  }
  struct ListNode* dummy = malloc(sizeof(struct ListNode));
  struct ListNode* tail = dummy;
  while (listOne != NULL && listTwo != NULL) {
    if (listOne->val < listTwo->val) {
      tail->next = listOne;
      listOne = listOne->next;
    } else {
      tail->next = listTwo;
      listTwo = listTwo->next;
    }
    tail = tail->next;
  }
  tail->next = listOne != NULL ? listOne : listTwo;
  return dummy->next;
}

/**
 * @brief 解法二：优先队列
 * @param[in] lists 一个数组，其中的元素是链表的头节点
 * @param[in] listsSize 数组大小
 * @return 合并后的升序链表
 */
static struct ListNode* solutionTwo(struct ListNode** lists, int listsSize) {
  if (listsSize == 0) return NULL;
  struct ListNode* dummy = calloc(1, sizeof(struct ListNode));
  struct ListNode* tail = dummy;
  struct ListNode* queue[listsSize];  // 优先队列
  int size = 0;  // 当前队列元素大小
  /* 构建大小为 K 个元素的小顶堆 */
  for (int i = 0; i < listsSize; i++) {
    offer(queue, &size, lists[i]);
  }
  /* 堆顶元素出堆，然后入堆元素为出堆元素的下一个节点 */
  while (size > 0) {
    struct ListNode* node = pop(queue, &size);
    tail->next = node;
    tail = tail->next;
    if (node->next != NULL) {
      offer(queue, &size, node->next);
    }
  }
  return dummy->next;
}

/**
 * @brief 元素入队操作
 * @param[in, out] queue 优先队列
 * @param[in] size 当前队列大小
 * @param[in] node 要入队的元素
 */
static void offer(struct ListNode** queue, int* size, struct ListNode* node) {
  if (node == NULL) return;
  /* 加入队尾，然后进行自下而上的堆化 */
  queue[(*size)++] = node;
  /* 要保证父节点是存在的 */
  for (int i = *size - 1, parent = (i - 1) / 2; parent >= 0; i = parent, parent = (i - 1) / 2) {
    /* 父节点比当前节点大则交换位置 */
    if (queue[parent]->val > queue[i]->val) {
      struct ListNode* temp = queue[parent];
      queue[parent] = queue[i];
      queue[i] = temp;
    } else {
      break;
    }
  }
}

/**
 * @brief 元素出队操作
 * @param[in, out] queue 优先队列
 * @param[in] size 当前队列大小
 */
static struct ListNode* pop(struct ListNode** queue, int* size) {
  struct ListNode* node = queue[0];
  queue[0] = queue[(*size)-- - 1]; /* 队尾元素赋值给队头 */
  /* 进行自上而下的堆化，这里循环的条件是要保证当前节点具有左子节点 */
  for (int i = 0, child = 1; child < *size; i = child, child = (i + 1) * 2 - 1) {
    /* 这里要保证右子节点有值，然后找到两个子节点中的最小的节点 */
    if (child + 1 < *size && queue[child]->val > queue[child + 1]->val) child += 1;
    if (queue[i]->val < queue[child]->val) break;  // 当前节点如果是最小的，则无需进行交换
    struct ListNode* temp = queue[i];
    queue[i] = queue[child];
    queue[child] = temp;
  }
  return node;
}
