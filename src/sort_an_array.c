#include "leetcode/sort_an_array.h"

#include <stdlib.h>
#include <stdbool.h>

static int* bubbleSort(int*, int, int*);
static int* quickSort(int*, int, int*);
static int* quickSortHelper(int*, int, int);
static int* selectionSort(int*, int, int*);
static int* insertionSort(int*, int, int*);
static int* heapSort(int*, int, int*);
static void siftDown(int*, int, int);
static int* mergeSort(int*, int, int*);
static void mergeSortHelper(int*, int, int);

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
  // return selectionSort(nums, numsSize, returnSize);
  // return insertionSort(nums, numsSize, returnSize);
  // return heapSort(nums, numsSize, returnSize);
  return mergeSort(nums, numsSize, returnSize);
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

/**
 * @brief 插入排序
 * @note 稳定排序，时间复杂度 O(n^2)
 * @param[in] nums 输入数组
 * @param[in] numsSize 输入数组大小
 * @param[out] returnSize 输出数组大小
 * @return 排序后的数组
 */
static int* insertionSort(int* nums, int numsSize, int* returnSize) {
  for (int i = 1; i < numsSize; i++) {
    int cur = nums[i], j = i - 1;
    while (j >= 0 && nums[j] > cur) {
      nums[j + 1] = nums[j];
      j--;
    }
    nums[j + 1] = cur;
  }
  *returnSize = numsSize;
  return nums;
}

/**
 * @brief 堆排序
 * @note 不稳定排序，平均时间复杂度 O(nlogn)，最坏时间复杂度 O(nlogn)
 * @param[in] nums 输入数组
 * @param[in] numsSize 输入数组大小
 * @param[out] returnSize 输出数组大小
 * @return 排序后的数组
 */
static int* heapSort(int* nums, int numsSize, int* returnSize) {
  /* 构建最大堆，查找最后一个非叶子节点的索引 */
  for (int i = numsSize / 2 - 1; i >= 0; i--) {
    siftDown(nums, numsSize, i);
  }
  for (int end = numsSize - 1; end > 0; end--) {
    /* 交换首尾元素 */
    nums[0] ^= nums[end];
    nums[end] ^= nums[0];
    nums[0] ^= nums[end];
    /* 重新调整堆 */
    siftDown(nums, end, 0);
  }
  *returnSize = numsSize;
  return nums;
}

/**
 * @brief 自顶向下堆化
 * @param[in] nums 输入数组
 * @param[in] size 数组大小
 * @param[in] start 堆化的起始位置
 */
static void siftDown(int* nums, int size, int start) {
  int parent = start;
  while (parent < size) {
    int child = parent * 2 + 1;
    if (child >= size) break;
    if (child + 1 < size && nums[child] < nums[child + 1]) child++;
    if (nums[parent] > nums[child]) break;
    nums[parent] ^= nums[child];
    nums[child] ^= nums[parent];
    nums[parent] ^= nums[child];
    parent = child;
  }
}

/**
 * @brief 归并排序
 * @note 稳定排序，平均时间复杂度 O(nlogn)
 * @param[in] nums 输入数组
 * @param[in] numsSize 输入数组大小
 * @param[out] returnSize 输出数组大小
 * @return 排序后的数组
 */
static int* mergeSort(int* nums, int numsSize, int* returnSize) {
  mergeSortHelper(nums, 0, numsSize - 1);
  *returnSize = numsSize;
  return nums;
}

/**
 * @brief 归并排序辅助函数
 * @param[in] nums 输入数组
 * @param[in] left 当前递归的左边界
 * @param[in] right 当前递归的右边界
 */
static void mergeSortHelper(int* nums, int left, int right) {
  if (left >= right) return;
  /* 划分阶段 */
  int mid = (left + right) / 2;
  mergeSortHelper(nums, left, mid);
  mergeSortHelper(nums, mid + 1, right);
  /* 合并阶段 */
  int len = right - left + 1;
  int* temp = (int*)malloc(len * sizeof(int));
  int p = left, q = mid + 1, i = 0;
  while (i < len && p <= mid && q <= right) {
    temp[i++] = nums[p] < nums[q] ? nums[p++] : nums[q++];
  }
  /* 剩余的元素加入数组中 */
  while (p <= mid) {
    temp[i++] = nums[p++];
  }
  while (q <= right) {
    temp[i++] = nums[q++];
  }
  /* 将排序后的元素复制回原数组 */
  for (i = 0; i < len; i++) {
    nums[left + i] = temp[i];
  }
  free(temp);
}
