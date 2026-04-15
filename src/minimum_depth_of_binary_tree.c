#include "leetcode/minimum_depth_of_binary_tree.h"

#include <stdlib.h>

/**
 * @brief LeetCode 111. 二叉树的最小深度
 * @link https://leetcode.com/problems/minimum-depth-of-binary-tree/
 * @param[in] root 二叉树的根节点
 * @return 二叉树的最小深度
 */
int minDepth(struct TreeNode* root) {
  if (root == NULL) return 0;
  int leftDepth = minDepth(root->left);
  int rightDepth = minDepth(root->right);
  /* 这里要判断是否只有一个子节点的情况 */
  if (root->left == NULL || root->right == NULL) {
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
  }
  return (leftDepth < rightDepth ? leftDepth : rightDepth) + 1;
}
