#include "utils/multi_tree_utils.h"

#include <vector>

namespace MultiTreeUtils {

struct Node* createTreeFromArray(const std::vector<int>& arr) {
  struct Node* dummy = (struct Node*)calloc(1, sizeof(struct Node));
  struct Node* cur = dummy;
  std::vector<struct Node*> stack;
  int index = 0;
  for (int i = 0; i < arr.size();) {
    if (arr[i] == NULL) {
      cur = stack[index++];
      i++;
    } else {
      int size = 0;
      for (int j = i; arr[j] != NULL; j++) size++;
      cur->children = (struct Node**)malloc(sizeof(struct Node*) * size);
      for (int j = 0; j < size; j++) {
        struct Node* newNode = (struct Node*)calloc(1, sizeof(struct Node));
        newNode->val = arr[i + j];
        cur->children[j] = newNode;
        cur->numChildren++;
        stack.push_back(newNode);
      }
      i += size;
    }
  }
  return (dummy->children)[0];
}

void freeTree(struct Node* root) {
  if (root == nullptr) return;
  for (int i = 0; i < root->numChildren; i++) {
    freeTree(root->children[i]);
  }
  delete[] root->children;
  delete root;
}

std::vector<int> treeToVector(int* arr, int size) {
  std::vector<int> result;
  for (int i = 0; i < size; i++) {
    result.push_back(arr[i]);
  }
  return result;
}
}  // namespace MultiTreeUtils
