#pragma once

#include <vector>

#include "leetcode/common/multi_tree.h"

namespace MultiTreeUtils {

struct Node* createTreeFromArray(const std::vector<int>&);

void freeTree(struct Node*);

std::vector<int> treeToVector(int*, int);

}  // namespace MultiTreeUtils
