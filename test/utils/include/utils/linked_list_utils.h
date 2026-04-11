#pragma once

#include <vector>

struct ListNode {
  int val;
  struct ListNode* next;
};

struct ListNode* createListFromArray(std::vector<int>);

void freeList(struct ListNode*);

std::vector<int> listToVector(struct ListNode*);
