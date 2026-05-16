#include <stdlib.h>

/**
 * @brief Leetcode 370. 区间加法 🔒
 * @link https://leetcode.cn/problems/range-addition/
 * @note 这里需要构造一个差分数组来实现区间加法的高效更新。差分数组的定义是：diff[i] = arr[i] - arr[i-1]，
 *       若要对区间 [i, j] 加上一个值 val，我们可以在差分数组的 diff[i] 上加上 val，在 diff[j + 1] 上减去 val。
 *       最后，我们可以通过对差分数组进行前缀和来得到最终的结果数组。
 * @param[in] length 数组长度
 * @param[in] updates 更新操作列表
 * @param[in] updatesSize 更新操作的数量
 * @param[in] updatesColSize 每个更新操作的列数，固定为 3
 * @param[out] returnSize 返回数组的大小
 * @return 返回修改后的数组
 */
int* getModifiedArray(int length, int** updates, int updatesSize, int* updatesColSize, int* returnSize) {
  int* diff = (int*)calloc(length, sizeof(int));  // 初始化差分数组
  *returnSize = length;
  /* 执行 updates 中的操作 */
  for (int i = 0; i < updatesSize; i++) {
    int start = updates[i][0];
    int end = updates[i][1];
    int incrment = updates[i][2];
    diff[start] += incrment;
    if (end + 1 < length) {
      diff[end + 1] -= incrment;
    }
  }
  /* 还原数组 */
  for (int i = 1; i < length; i++) {
    diff[i] += diff[i - 1];
  }
  return diff;
}
