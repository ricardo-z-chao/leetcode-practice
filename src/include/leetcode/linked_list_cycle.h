#pragma once

#include <stdbool.h>

struct ListNode {
  int val;
  struct ListNode* next;
};

bool hasCycle(struct ListNode*);
