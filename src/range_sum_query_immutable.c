/**
 * @brief LeetCode 303. 区域和检索 - 数组不可变
 * @link https://leetcode-cn.com/problems/range-sum-query-immutable/
 * @note 每次调用numArraySumRange时，都需要使用循环来遍历数组，可以在构造函数中提前计算前缀和，优化查询效率。
 */

#include "leetcode/range_sum_query_immutable.h"

#include <stdlib.h>

/**
 * @brief 构造函数，输入一个整数数组 nums，初始化 NumArray 对象
 * @param[in] nums 输入的整数数组
 * @param[in] numsSize 输入数组的大小
 * @return 返回构造的 NumArray 对象
 */
NumArray* numArrayCreate(int* nums, int numsSize) {
  NumArray* obj = (NumArray*)malloc(sizeof(NumArray));
  obj->sum = (int*)malloc((numsSize + 1) * sizeof(int));
  obj->sum[0] = 0;
  for (int i = 0; i < numsSize; i++) {
    obj->sum[i + 1] = obj->sum[i] + nums[i];
  }
  return obj;
}

/**
 * @brief 计算从索引 left 到 right（包含 left 和 right）范围内元素的总和
 * @param[in] obj NumArray 对象
 * @param[in] left 范围的左边界索引
 * @param[in] right 范围的右边界索引
 * @return 返回范围内元素的总和
 */
int numArraySumRange(NumArray* obj, int left, int right) {
  return obj->sum[right + 1] - obj->sum[left];
}

/**
 * @brief 释放 NumArray 对象占用的内存
 * @param[in] obj NumArray 对象
 */
void numArrayFree(NumArray* obj) {
  free(obj->sum);
  free(obj);
}
