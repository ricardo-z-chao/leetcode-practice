#pragma once

struct ListNode {
  int val;
  struct ListNode* next;
};

struct ListNode* reverseBetween(struct ListNode*, int, int);
