#include "leetcode/binary_tree_postorder_traversal.h"

#include <stdlib.h>

int* dfs_one(struct TreeNode*, int[], int*);
int* dfs_two(struct TreeNode*, int[], int*);

/**
 * @brief LeetCode 145. 二叉树的后序遍历
 * @link https://leetcode.cn/problems/binary-tree-postorder-traversal/
 * @param[in] root 二叉树根节点
 * @param[out] returnSize 返回数组大小
 * @return 后序遍历结果数组
 */
int* postorderTraversal(struct TreeNode* root, int* returnSize) {
  int* result = (int*)malloc(sizeof(int) * 100);
  *returnSize = 0;
  // return dfs_one(root, result, returnSize);
  return dfs_two(root, result, returnSize);
}

/**
 * @brief 方法一：递归实现
 * @param[in] root 二叉树根节点
 * @param[out] returnSize 返回数组大小
 * @return 后序遍历结果数组
 */
int* dfs_one(struct TreeNode* root, int result[], int* returnSize) {
  if (root == NULL) return NULL;
  dfs_one(root->left, result, returnSize);
  dfs_one(root->right, result, returnSize);
  result[(*returnSize)++] = root->val;
  return result;
}

/**
 * @brief 方法二：迭代实现
 * @param[in] root 二叉树根节点
 * @param[out] returnSize 返回数组大小
 * @return 后序遍历结果数组
 */
int* dfs_two(struct TreeNode* root, int result[], int* returnSize) {
  if (root == NULL) return NULL;
  struct TreeNode* stack[100];
  int top = -1;
  struct TreeNode* cur = root;
  struct TreeNode* prev = NULL; /* 记录上一个访问的节点 */
  while (cur != NULL || top > -1) {
    while (cur != NULL) {
      stack[++top] = cur;
      cur = cur->left;
    }
    cur = stack[top--];
    /* 这里需要判断是不是从右子树返回的 */
    if (cur->right == NULL || prev == cur->right) {
      result[(*returnSize)++] = cur->val;
      prev = cur;
      cur = NULL;
    } else {
      stack[++top] = cur;
      cur = cur->right;
    }
  }
  return result;
}
