#pragma once

struct ListNode {
  int val;
  struct ListNode* next;
};

struct ListNode* partition(struct ListNode*, int);
