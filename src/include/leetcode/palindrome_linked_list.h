#pragma once

#include <stdbool.h>

struct ListNode {
  int val;
  struct ListNode* next;
};

bool isPalindrome(struct ListNode*);
