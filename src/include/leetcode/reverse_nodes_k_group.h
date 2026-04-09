#pragma once

struct ListNode {
  int val;
  struct ListNode* next;
};

struct ListNode* reverseKGroup(struct ListNode*, int);
