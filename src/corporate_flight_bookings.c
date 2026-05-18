#include <stdlib.h>

/**
 * @brief LeetCode 1109. 航班预订统计
 * @link https://leetcode.cn/problems/corporate-flight-bookings/
 * @param[in] bookings 航班预订列表
 * @param[in] bookingsSize 航班预订列表的大小
 * @param[in] bookingsColSize 航班预订列表中每个子列表的大小
 * @param[in] n 航班数量
 * @param[in] returnSize 返回数组的大小
 * @return 返回修改后的数组
 */
int* corpFlightBookings(int** bookings, int bookingsSize, int* bookingsColSize, int n, int* returnSize) {
  int* diff = (int*)calloc(n, sizeof(int));
  *returnSize = n;
  for (int i = 0; i < bookingsSize; i++) {
    int start = bookings[i][0] - 1, end = bookings[i][1], incr = bookings[i][2];
    diff[start] += incr;
    if (end < n) {
      diff[end] -= incr;
    }
  }
  /* 还原数组 */
  for (int i = 1; i < n; i++) {
    diff[i] += diff[i - 1];
  }
  return diff;
}
