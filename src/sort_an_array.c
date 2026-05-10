#include "leetcode/sort_an_array.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static int* bubbleSort(int*, int, int*);
static int* quickSort(int*, int, int*);
static int* quickSortHelper(int*, int, int);
static int* selectionSort(int*, int, int*);
static int* insertionSort(int*, int, int*);
static int* heapSort(int*, int, int*);
static void siftDown(int*, int, int);
static int* mergeSort(int*, int, int*);
static void mergeSortHelper(int*, int, int);
static int* countingSort(int*, int, int*);
static int* bucketSort(int*, int, int*);
static int compareInt(const void*, const void*);

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
  // return mergeSort(nums, numsSize, returnSize);
  // return countingSort(nums, numsSize, returnSize);
  return bucketSort(nums, numsSize, returnSize);
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

/**
 * @brief 计数排序
 * @note 稳定排序，时间复杂度 O(n+m)，其中 m 是输入数据的范围。
 *       1. 当数列最大值和最小值差距过大时，并不适合用计数排序
 *       2. 计数排序只适合对整数进行排序
 * @param[in] nums 输入数组
 * @param[in] numsSize 输入数组大小
 * @param[out] returnSize 输出数组大小
 * @return 排序后的数组
 */
static int* countingSort(int* nums, int numsSize, int* returnSize) {
  /* 获取数列最大值和最小值 */
  int max = nums[0], min = nums[0];
  for (int i = 1; i < numsSize; i++) {
    if (nums[i] > max) max = nums[i];
    if (nums[i] < min) min = nums[i];
  }
  /* 创建统计数组 */
  int len = max - min + 1;
  int* counter = (int*)calloc(len, sizeof(int));
  /* 统计每个元素出现的次数 */
  for (int i = 0; i < numsSize; i++) {
    /* 这里需要减去最小值作为偏移量 */
    counter[nums[i] - min]++;
  }
  /* 计算前缀和 */
  for (int i = 1; i < len; i++) {
    counter[i] += counter[i - 1];
  }
  /* 从后往前遍历原数组 */
  int* sorted = (int*)malloc(numsSize * sizeof(int));
  for (int i = numsSize - 1; i >= 0; i--) {
    sorted[counter[nums[i] - min]-- - 1] = nums[i];
  }
  memcpy(nums, sorted, numsSize * sizeof(int));
  free(counter);
  free(sorted);
  *returnSize = numsSize;
  return nums;
}

/**
 * @brief 桶排序
 * @note 稳定排序，平均时间复杂度 O(n+m)，其中 m 是桶的数量。当输入数据分布较为均匀时，桶排序的效率较高。
 *       如何确定桶的数量和范围，通常没有唯一的数学公式，而是根据数据分布和性能目标来权衡。
 * @param[in] nums 输入数组
 * @param[in] numsSize 输入数组大小
 * @param[out] returnSize 输出数组大小
 * @return 排序后的数组
 */
static int* bucketSort(int* nums, int numsSize, int* returnSize) {
  /* 计算最大值和最小值 */
  int max = nums[0], min = nums[0];
  for (int i = 1; i < numsSize; i++) {
    if (nums[i] > max) max = nums[i];
    if (nums[i] < min) min = nums[i];
  }
  int bucketScope = 5; /* 桶的宽度，这里假设为5，在实际使用时需要根据数据的分布来决定 */
  int bucketNum = (max - min + 1) / bucketScope + 1; /* 桶的数量，加 1 表示保证至少要有一个桶 */
  int initialCapacity = numsSize / bucketNum + 1; /* 初始桶的大小，可以根据实际情况调整 */
  int** buckets = (int**)malloc(bucketNum * sizeof(int*)); /* 创建桶 */
  int* bucketSizes = (int*)calloc(bucketNum, sizeof(int)); /* 记录每个桶的大小 */
  int* bucketCapacities = (int*)malloc(bucketNum * sizeof(int)); /* 记录每个桶的容量 */
  /* 为每个桶的容量设置足够的大小 */
  for (int i = 0; i < bucketNum; i++) {
    buckets[i] = (int*)malloc(initialCapacity * sizeof(int));
    bucketCapacities[i] = initialCapacity;
  }
  /* 将元素分配的桶中 */
  for (int i = 0; i < numsSize; i++) {
    int bucketIndex = (nums[i] - min) / bucketScope;
    /* 处理边界问题 */
    if (bucketIndex >= bucketNum) bucketIndex = bucketNum - 1;
    /* 扩容 */
    if (bucketSizes[bucketIndex] >= bucketCapacities[bucketIndex]) {
      buckets[bucketIndex] = (int*)realloc(buckets[bucketIndex], bucketCapacities[bucketIndex] * 2 * sizeof(int));
      bucketCapacities[bucketIndex] *= 2;
    }
    buckets[bucketIndex][bucketSizes[bucketIndex]++] = nums[i];
  }
  /* 对每个桶进行排序，这里可以使用内置快速排序对桶进行排序 */
  for (int i = 0; i < bucketNum; i++) {
    if (bucketSizes[i] > 0) {
      qsort(buckets[i], bucketSizes[i], sizeof(int), compareInt);
    }
  }
  /* 合并桶 */
  *returnSize = 0;
  for (int i = 0; i < bucketNum; i++) {
    for (int j = 0; j < bucketSizes[i]; j++) {
      nums[(*returnSize)++] = buckets[i][j];
    }
    free(buckets[i]);
  }
  free(buckets);
  free(bucketSizes);
  free(bucketCapacities);
  return nums;
}

/**
 * @brief 比较函数，用于 qsort 进行排序
 * @param[in] a 第一个元素的指针
 * @param[in] b 第二个元素的指针
 * @return a 和 b 的差值，正数表示 a 大于 b，负数表示 a 小于 b，零表示 a 和 b 相等
 */
int compareInt(const void* a, const void* b) {
  return (*(int*)a - *(int*)b);
}
