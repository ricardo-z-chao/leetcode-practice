#pragma once

struct Node {
  int val;
  int numChildren;
  struct Node** children;
};
