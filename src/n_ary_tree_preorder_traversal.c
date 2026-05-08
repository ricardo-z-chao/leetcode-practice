#include "leetcode/n_ary_tree_preorder_traversal.h"

#include <stdlib.h>

#define NODE_MAXIMUM 10000

int* solution_one(struct Node*, int[], int*);
int* solution_two(struct Node*, int[], int*);

/**
 * @brief LeetCode 589. N 叉树的前序遍历
 * @link https://leetcode.cn/problems/n-ary-tree-preorder-traversal/
 * @param root n 叉树的根节点
 * @param returnSize 返回数组的大小
 * @return 前序遍历结果数组
 */
int* preorder(struct Node* root, int* returnSize) {
  int* result = (int*)malloc(sizeof(int) * NODE_MAXIMUM);
  *returnSize = 0;
  // return solution_one(root, result, returnSize);
  return solution_two(root, result, returnSize);
}

/**
 * @brief 方法一：递归实现
 * @param root n 叉树的根节点
 * @param result 前序遍历结果数组
 * @param returnSize 返回数组的大小
 * @return 前序遍历结果数组
 */
int* solution_one(struct Node* root, int result[], int* returnSize) {
  if (root == NULL) return result;
  result[(*returnSize)++] = root->val;
  for (int i = 0; i < root->numChildren; i++) {
    solution_one((root->children)[i], result, returnSize);
  }
  return result;
}

/**
 * @brief 方法二：迭代实现
 * @param root n 叉树的根节点
 * @param result 前序遍历结果数组
 * @param returnSize 返回数组的大小
 * @return 前序遍历结果数组
 */
int* solution_two(struct Node* root, int result[], int* returnSize) {
  if (root == NULL) return result;
  struct Node* stack[NODE_MAXIMUM] = {root}; /* 定义栈 */
  int stackSize = 1; /* 当前栈大小 */
  while (stackSize > 0) {
    /* 出栈 */
    struct Node* top = stack[stackSize-- - 1];
    result[(*returnSize)++] = top->val;
    /* 倒序入栈 */
    for (int i = top->numChildren - 1; i >= 0; i--) {
      stack[stackSize++] = (top->children)[i];
    }
  }
  return result;
}
