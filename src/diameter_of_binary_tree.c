#include "leetcode/diameter_of_binary_tree.h"

#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int depth(struct TreeNode*, int*);

/**
 * @brief LeetCode 543. 二叉树的直径
 * @link https://leetcode-cn.com/problems/diameter-of-binary-tree/
 * @note 这里需要记录以当前节点为根节点的树的高度，然后更新直径。
 *       直径是左子树和右子树高度和加1，需要注意的是，子树的直径可能会大于以当前节点为根节点的树的直径，所以需要在递归过程中更新直径。
 * @param[in] root 二叉树的根节点
 * @return 二叉树的直径
 */
int diameterOfBinaryTree(struct TreeNode* root) {
  int diameter = 1;
  depth(root, &diameter);
  return diameter - 1;
}

/**
 * @brief 计算以当前节点为根节点的树的高度，并更新直径
 * @param[in] root 当前节点
 * @param[in,out] diameter 直径的指针，用于更新直径
 * @return 以当前节点为根节点的树的高度
 */
int depth(struct TreeNode* root, int* diameter) {
  if (root == NULL) return 0;
  int leftDepth = depth(root->left, diameter);
  int rightDepth = depth(root->right, diameter);
  *diameter = MAX(*diameter, leftDepth + rightDepth + 1);
  return MAX(leftDepth, rightDepth) + 1;
}
