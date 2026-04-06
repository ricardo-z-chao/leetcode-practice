#pragma once

struct ListNode {
  int val;
  struct ListNode* next;
};

struct ListNode* getIntersectionNode(struct ListNode*, struct ListNode*);
