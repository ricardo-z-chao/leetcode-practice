#pragma once

typedef struct {
  int** sum;
  int rows;
  int cols;
} NumMatrix;


NumMatrix* numMatrixCreate(int**, int, int*);

int numMatrixSumRegion(NumMatrix*, int, int, int, int);

void numMatrixFree(NumMatrix*);
