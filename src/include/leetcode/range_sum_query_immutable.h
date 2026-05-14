#pragma once

typedef struct {
  int* sum; /* 前缀和数组 */
} NumArray;

NumArray* numArrayCreate(int*, int);

int numArraySumRange(NumArray*, int, int);

void numArrayFree(NumArray*);
