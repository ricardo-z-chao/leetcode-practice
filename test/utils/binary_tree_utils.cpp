#include "utils/binary_tree_utils.h"

#include <vector>

struct TreeNode* createTreeFromArray(const std::vector<int>& arr) {
  if (arr.empty() || arr[0] == NULL) return NULL;
  struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
  root->val = arr[0];
  root->left = NULL;
  root->right = NULL;

  std::vector<struct TreeNode*> nodes;
  nodes.push_back(root);

  size_t i = 0;
  while (i < nodes.size()) {
    struct TreeNode* current = nodes[i];
    size_t leftIdx = 2 * i + 1;
    size_t rightIdx = 2 * i + 2;

    if (leftIdx < arr.size() && arr[leftIdx] != NULL) {
      struct TreeNode* leftNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
      leftNode->val = arr[leftIdx];
      leftNode->left = NULL;
      leftNode->right = NULL;
      current->left = leftNode;
      nodes.push_back(leftNode);
    }

    if (rightIdx < arr.size() && arr[rightIdx] != NULL) {
      struct TreeNode* rightNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
      rightNode->val = arr[rightIdx];
      rightNode->left = NULL;
      rightNode->right = NULL;
      current->right = rightNode;
      nodes.push_back(rightNode);
    }

    i++;
  }

  return root;
}

void freeTree(struct TreeNode* root) {
  if (root == NULL) return;
  freeTree(root->left);
  freeTree(root->right);
  free(root);
}

std::vector<int> treeToVector(int* arr, int size) {
  std::vector<int> result;
  for (int i = 0; i < size; i++) {
    result.push_back(arr[i]);
  }
  return result;
}
