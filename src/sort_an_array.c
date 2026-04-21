#include "leetcode/sort_an_array.h"

#include <stdlib.h>
#include <stdbool.h>

static int* bubbleSort(int*, int, int*);

/**
 * @berief leetcode 912. 排序数组
 * @link https://leetcode-cn.com/problems/sort-an-array/
 * @param[in] nums 输入数组
 * @param[in] numsSize 输入数组大小
 * @param[out] returnSize 输出数组大小
 * @return 排序后的数组
 */
int* sortArray(int* nums, int numsSize, int* returnSize) {
  return bubbleSort(nums, numsSize, returnSize);
}

/**
 * @brief 冒泡排序
 * @note 稳定排序，时间复杂度 O(n^2)
 * @param[in] nums 输入数组
 * @param[in] numsSize 输入数组大小
 * @param[out] returnSize 输出数组大小
 * @return 排序后的数组
 */
static int* bubbleSort(int* nums, int numsSize, int* returnSize) {
  for (int i = numsSize - 1; i > 0; i--) {
    /* 这里来记录当前轮是不是有序的，如果没有元素交换则表示是有序的，就不必要继续进行下一轮了 */
    bool isSorted = true;
    /* 记录最后一个交换的元素位置，如果后面的元素都是有序的，则不需要进行后续的比较 */
    int lastSwapIndex = 0, length = i;
    for (int j = 0; j < length; j++) {
      if (nums[j] > nums[j + 1]) {
        nums[j] ^= nums[j + 1];
        nums[j + 1] ^= nums[j];
        nums[j] ^= nums[j + 1];
        isSorted = false;
        lastSwapIndex = j;
      }
    }
    /* 记录无序区的长度 */
    length = lastSwapIndex;
    if (isSorted) break;
  }
  *returnSize = numsSize;
  return nums;
}
