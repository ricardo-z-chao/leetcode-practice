#include "leetcode/n_ary_tree_level_order_traversal.h"

#include <stdlib.h>

#define NODE_MAXIMUM 10000
#define LEVEL_MAXIMUM 1000

/**
 * @brief LeetCode 429. N 叉树的层序遍历
 * @link https://leetcode.com/problems/n-ary-tree-level-order-traversal/
 * @param[in] root N 叉树的根节点
 * @param[out] returnSize 返回的二维数组的行数
 * @param[out] returnColumnSizes 返回的二维数组每行的列数
 * @return N 叉树的层序遍历结果
 */
int** levelOrder(struct Node* root, int* returnSize, int** returnColumnSizes) {
  int** result = (int**)malloc(sizeof(int*) * LEVEL_MAXIMUM);
  *returnColumnSizes = (int*)malloc(sizeof(int) * LEVEL_MAXIMUM);
  *returnSize = 0;
  if (root == NULL) return NULL;
  struct Node* queue[NODE_MAXIMUM + 1] = {root};
  int head = 0, tail = 1;
  /* 当队列不为空则出队首，然后入队尾 */
  while (tail - head > 0) {
    int len = tail - head; /* 记录出队元素的数量 */
    int* levelNodes = (int*)malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++) {
      /* 出队 */
      struct Node* node = queue[head++];
      levelNodes[i] = node->val;
      /* 入队 */
      for (int j = 0; j < node->numChildren; j++) {
        queue[tail++] = node->children[j];
      }
    }
    result[(*returnSize)] = levelNodes;
    (*returnColumnSizes)[(*returnSize)++] = len;
  }
  return result;
}
