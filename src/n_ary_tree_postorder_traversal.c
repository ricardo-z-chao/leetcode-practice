#include "leetcode/n_ary_tree_postorder_traversal.h"

#include <stdlib.h>

#define NODE_MAXIMUM 10000

int* solution_one(struct Node*, int[], int*);
int* solution_two(struct Node*, int[], int*);

/**
 * @brief Leetcode 590. N 叉树的后序遍历
 * @link https://leetcode.cn/problems/n-ary-tree-postorder-traversal/
 * @param[in] root n 叉树的根节点
 * @param[out] returnSize 返回数组的大小
 * @return 后序遍历结果数组
 */
int* postorder(struct Node* root, int* returnSize) {
  int* result = (int*)malloc(sizeof(int) * NODE_MAXIMUM);
  *returnSize = 0;
  // return solution_one(root, result, returnSize);
  return solution_two(root, result, returnSize);
}

/**
 * @brief 方法一：递归
 * @param[in] root n 叉树的根节点
 * @param[out] result 后序遍历结果数组
 * @param[out] returnSize 返回数组的大小
 * @return 后序遍历结果数组
 */
int* solution_one(struct Node* root, int result[], int* returnSize) {
  if (root == NULL) return NULL;
  for (int i = 0; i < root->numChildren; i++) {
    solution_one(root->children[i], result, returnSize);
  }
  result[(*returnSize)++] = root->val;
  return result;
}

/**
 * @brief 方法二：迭代
 * @param[in] root n 叉树的根节点
 * @param[out] result 后序遍历结果数组
 * @param[out] returnSize 返回数组的大小
 * @return 后序遍历结果数组
 */
int* solution_two(struct Node* root, int result[], int* returnSize) {
  if (root == NULL) return NULL;
  struct Node* stack[NODE_MAXIMUM] = {root};
  int size = 1;
  /* 这里要额外维护一个非叶子节点栈来记录已经入栈的非叶子节点 */
  struct Node* visited[NODE_MAXIMUM] = {NULL};
  int visitedSize = 1;
  struct Node* parent = NULL;
  while (size > 0) {
    struct Node* top = stack[size - 1];
    /* 如果当前元素有子节点，倒序入栈，节点入栈之前需要判断这个节点是否被访问过，防止出栈的时候再次入栈一遍子节点 */
    if (top->numChildren > 0 && top != visited[visitedSize - 1]) {
      visited[visitedSize++] = top;
      for (int i = top->numChildren - 1; i >= 0; i--) {
        stack[size++] = top->children[i];
      }
    } else {
      /* 判断当前出栈的元素是否为非叶子节点 */
      if (top == visited[visitedSize - 1]) visitedSize--;
      result[(*returnSize)++] = top->val;
      size--;
    }
  }
  return result;
}
