#include "leetcode/binary_tree_level_order_traversal.h"

#include <stdlib.h>

/**
 * @brief LeetCode 102. 二叉树的层序遍历
 * @link https://leetcode.cn/problems/binary-tree-level-order-traversal/
 * @note 树中节点数目在范围 [0, 2000] 内，由此可知二叉树层数最少为 11，最多为 2000
 *       因为 2^11 - 1 = 2047
 * @param[in] root 二叉树根节点
 * @param[out] returnSize 返回的二维数组行数
 * @param[out] returnColumnSizes 返回的二维数组每行元素个数
 * @return 二维数组，每行元素为二叉树每层的节点值
 */
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
  const int MAX_LEVEL = 2000;  // 最大层数
  struct TreeNode* queue[2001] = {root};
  int head = 0, tail = 1;
  /* 初始化 */
  int** result = (int**)malloc(sizeof(int*) * MAX_LEVEL);
  *returnSize = 0;
  *returnColumnSizes = calloc(MAX_LEVEL, sizeof(int));
  int nextLevelCount = 1;  // 下一层的元素数量
  while (root != NULL && tail - head > 0) {
    int count = 0;  // 用于统计每层出队元素需要入队多少元素
    /* 根据下一层的元素数量来计算每层需要出队几个元素 */
    result[*returnSize] = malloc(sizeof(int) * nextLevelCount);
    for (int i = 0; i < nextLevelCount; i++) {
      /* 加入结果中 */
      result[*returnSize][i] = root->val;
      /* 入队 */
      if (root->left != NULL) {
        queue[tail++] = root->left;
        count++;
      }
      if (root->right != NULL) {
        queue[tail++] = root->right;
        count++;
      }
      /* 出队 */
      root = queue[++head];
    }
    (*returnColumnSizes)[(*returnSize)++] = nextLevelCount;
    nextLevelCount = count;
  }
  return result;
}
