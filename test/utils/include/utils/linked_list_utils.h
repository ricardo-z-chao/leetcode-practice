#pragma once

#include <vector>

#include "leetcode/common/list.h"

namespace LinkedListUtils {

struct ListNode* createListFromArray(std::vector<int>);

void freeList(struct ListNode*);

std::vector<int> listToVector(struct ListNode*);

}  // namespace LinkedListUtils
