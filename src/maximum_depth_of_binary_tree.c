#include "leetcode/maximum_depth_of_binary_tree.h"

#include <stdlib.h>

/**
 * @brief Leetcode 104. 二叉树的最大深度
 * @link https://leetcode.com/problems/maximum-depth-of-binary-tree/
 * @param[in] root The root of the binary tree
 * @return The maximum depth of the binary tree
 */
int maxDepth(struct TreeNode* root) {
  if (root == NULL) return 0;
  int leftDepht = maxDepth(root->left);
  int rightDepth = maxDepth(root->right);
  return (leftDepht > rightDepth ? leftDepht : rightDepth) + 1;
}
