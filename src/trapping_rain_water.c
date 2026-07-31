#define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * @brief Leetcode 42. 接雨水
 * @link https://leetcode.cn/problems/trapping-rain-water/
 * @param[in] height 高度数组
 * @param[in] heightSize 高度数组大小
 * @return 接雨水的总量
 */
int trap(int* height, int heightSize) {
  int result = 0;
  int left = 0, right = heightSize - 1;
  int leftMax = 0, rightMax = 0;
  while (left < right) {
    if (height[left] <= height[right]) {
      leftMax = MAX(height[left], leftMax);
      result += (leftMax - height[left++]);
    } else {
      rightMax = MAX(height[right], rightMax);
      result += (rightMax - height[right--]);
    }
  }
  return result;
}
