#pragma once

#include <vector>

#include "leetcode/common/tree.h"

namespace BinaryTreeUtils {

struct TreeNode* createTreeFromArray(const std::vector<int>&);

void freeTree(struct TreeNode*);

std::vector<int> treeToVector(int*, int);

}  // namespace BinaryTreeUtils
