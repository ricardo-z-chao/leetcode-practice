#pragma once

struct ListNode {
  int val;
  struct ListNode* next;
};

struct ListNode* mergeKLists(struct ListNode**, int);
