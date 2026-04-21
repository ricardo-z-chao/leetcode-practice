#include "leetcode/sort_an_array.h"

#include <stdlib.h>

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
    for (int j = 0; j < i; j++) {
      if (nums[j] > nums[j + 1]) {
        nums[j] ^= nums[j + 1];
        nums[j + 1] ^= nums[j];
        nums[j] ^= nums[j + 1];
      }
    }
  }
  *returnSize = numsSize;
  return nums;
}
