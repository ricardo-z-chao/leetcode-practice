#pragma once

struct ListNode {
  int val;
  struct ListNode* next;
};

struct ListNode* detectCycle(struct ListNode*);
