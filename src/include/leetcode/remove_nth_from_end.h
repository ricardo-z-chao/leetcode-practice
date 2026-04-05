#pragma once

struct ListNode {
  int val;
  struct ListNode* next;
};

struct ListNode* removeNthFromEnd(struct ListNode*, int);
