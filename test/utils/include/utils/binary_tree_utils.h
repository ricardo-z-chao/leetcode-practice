#pragma once

#include <vector>

#include "leetcode/common/tree.h"

struct TreeNode* createTreeFromArray(const std::vector<int>&);

void freeTree(struct TreeNode*);

std::vector<int> treeToVector(int*, int);
