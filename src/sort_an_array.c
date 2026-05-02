#include "leetcode/sort_an_array.h"

#include <stdlib.h>
#include <stdbool.h>

static int* bubbleSort(int*, int, int*);
static int* quickSort(int*, int, int*);
static int* quickSortHelper(int*, int, int);
static int* selectionSort(int*, int, int*);

/**
 * @berief leetcode 912. 排序数组
 * @link https://leetcode-cn.com/problems/sort-an-array/
 * @param[in] nums 输入数组
 * @param[in] numsSize 输入数组大小
 * @param[out] returnSize 输出数组大小
 * @return 排序后的数组
 */
int* sortArray(int* nums, int numsSize, int* returnSize) {
  // return bubbleSort(nums, numsSize, returnSize);
  // return quickSort(nums, numsSize, returnSize);
  return selectionSort(nums, numsSize, returnSize);
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

/**
 * @brief 快速排序
 * @note 不稳定排序，平均时间复杂度 O(nlogn)，最坏时间复杂度 O(n^2)
 * @param[in] nums 输入数组
 * @param[in] numsSize 输入数组大小
 * @param[out] returnSize 输出数组大小
 * @return 排序后的数组
 */
static int* quickSort(int* nums, int numsSize, int* returnSize) {
  quickSortHelper(nums, 0, numsSize - 1);
  *returnSize = numsSize;
  return nums;
}

/**
 * @brief 快速排序辅助函数
 * @param[in] nums 输入数组
 * @param[in] left 当前递归的左边界
 * @param[in] right 当前递归的右边界
 * @return 排序后的数组
 */
static int* quickSortHelper(int* nums, int left, int right) {
  if (left >= right) return nums;
  /* 选取基准元素，这里用单边循环法来分隔数组，mark表示小区基准元素的边界 */
  int pivot = nums[left], mark = left;
  for (int i = left + 1; i <= right; i++) {
    /* 如果遍历到小于基准元素的元素则边界需要扩大 */
    if (nums[i] < pivot) {
      mark++;
      /* 交换元素位置，这里用异或运算要保证不是同一个位置的交换 */
      if (mark != i) {
        nums[mark] ^= nums[i];
        nums[i] ^= nums[mark];
        nums[mark] ^= nums[i];
      }
    }
  }
  /* 将基准元素放到边界位置 */
  nums[left] = nums[mark];
  nums[mark] = pivot;
  /* 递归处理左右两边的子数组 */
  quickSortHelper(nums, left, mark - 1);
  quickSortHelper(nums, mark + 1, right);
  return nums;
}

/**
 * @brief 选择排序
 * @note 不稳定排序，时间复杂度 O(n^2)
 * @param[in] nums 输入数组
 * @param[in] numsSize 输入数组大小
 * @param[out] returnSize 输出数组大小
 * @return 排序后的数组
 */
static int* selectionSort(int* nums, int numsSize, int* returnSize) {
  for (int i = 0; i < numsSize - 1; i++) {
    int minimumIndex = i;
    for (int j = i + 1; j < numsSize; j++) {
      if (nums[j] < nums[minimumIndex]) {
        minimumIndex = j;
      }
    }
    if (minimumIndex != i) {
      nums[minimumIndex] ^= nums[i];
      nums[i] ^= nums[minimumIndex];
      nums[minimumIndex] ^= nums[i];
    }
  }
  *returnSize = numsSize;
  return nums;
}
