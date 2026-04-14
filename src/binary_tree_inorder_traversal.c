#include "leetcode/binary_tree_inorder_traversal.h"

#include <stdlib.h>

int* dfs_one(struct TreeNode*, int[], int*);
int* dfs_two(struct TreeNode*, int[], int*);

/**
 * @brief LeetCode 94. 二叉树的中序遍历
 * @link https://leetcode.cn/problems/binary-tree-inorder-traversal/
 * @note 树中节点数在范围 [0, 100] 内
 * @param[in] root 二叉树根节点
 * @param[out] returnSize 返回数组大小
 * @return 中序遍历结果数组
 */
int* inorderTraversal(struct TreeNode* root, int* returnSize) {
  int* result = (int*)malloc(sizeof(int) * 100);
  *returnSize = 0;
  // return dfs_one(root, result, returnSize);
  return dfs_two(root, result, returnSize);
}

/**
 * @brief 方法一：递归
 * @param[in] root 二叉树根节点
 * @param[out] result 中序遍历结果数组
 * @param[out] returnSize 返回数组大小
 * @return 中序遍历结果数组
 */
int* dfs_one(struct TreeNode* root, int result[], int* returnSize) {
  if (root == NULL) return NULL;
  dfs_one(root->left, result, returnSize);
  result[(*returnSize)++] = root->val;
  dfs_one(root->right, result, returnSize);
  return result;
}

/**
 * @brief 方法二：迭代
 * @param[in] root 二叉树根节点
 * @param[out] result 中序遍历结果数组
 * @param[out] returnSize 返回数组大小
 * @return 中序遍历结果数组
 */
int* dfs_two(struct TreeNode* root, int result[], int* returnSize) {
  if (root == NULL) return NULL;
  struct TreeNode* stack[100];
  int top = -1;
  struct TreeNode* cur = root;
  while (cur != NULL || top > -1) {
    while (cur != NULL) {
      stack[++top] = cur;
      cur = cur->left;
    }
    cur = stack[top--];
    result[(*returnSize)++] = cur->val;
    cur = cur->right;
  }
  return result;
}
