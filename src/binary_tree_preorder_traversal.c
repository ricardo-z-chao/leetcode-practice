#include "leetcode/binary_tree_preorder_traversal.h"

#include <stdlib.h>

int* dfs_one(struct TreeNode*, int[], int*);
int* dfs_two(struct TreeNode*, int[], int*);

/**
 * @brief LeetCode 144. 二叉树的前序遍历
 * @link https://leetcode.cn/problems/binary-tree-preorder-traversal/
 * @note 树中节点数在范围 [0, 100] 内
 * @param[in] root 二叉树根节点
 * @param[out] returnSize 返回数组大小
 * @return 前序遍历结果数组
 */
int* preorderTraversal(struct TreeNode* root, int* returnSize) {
  int* result = (int*)malloc(sizeof(int) * 100);
  *returnSize = 0;
  // return dfs_one(root, result, returnSize);
  return dfs_two(root, result, returnSize);
}

/**
 * @brief 方法一：递归
 * @param[in] root 二叉树根节点
 * @param[out] result 前序遍历结果数组
 * @param[out] returnSize 返回数组大小
 * @return 前序遍历结果数组
 */
int* dfs_one(struct TreeNode* root, int result[], int* returnSize) {
  if (root == NULL) return NULL;
  result[(*returnSize)++] = root->val;
  dfs_one(root->left, result, returnSize);
  dfs_one(root->right, result, returnSize);
  return result;
}

/**
 * @brief 方法二：迭代
 * @param[in] root 二叉树根节点
 * @param[out] result 前序遍历结果数组
 * @param[out] returnSize 返回数组大小
 * @return 前序遍历结果数组
 */
int* dfs_two(struct TreeNode* root, int result[], int* returnSize) {
  struct TreeNode* stack[100];
  int top = -1;
  struct TreeNode* cur = root;
  /* 当栈不为空或者当前节点不为空时则继续循环 */
  while (cur != NULL || top > -1) {
    while (cur != NULL) {
      result[(*returnSize)++] = cur->val;
      stack[++top] = cur;
      cur = cur->left;
    }
    /* 栈顶元素出栈，访问右子节点 */
    cur = stack[top--]->right;
  }
  return result;
}
