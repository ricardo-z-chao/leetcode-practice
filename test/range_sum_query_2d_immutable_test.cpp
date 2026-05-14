extern "C" {
#include "leetcode/range_sum_query_2d_immutable.h"
}

#include "gtest/gtest.h"

class RangeSumQuery2dImmutableTest : public ::testing::Test {};

TEST_F(RangeSumQuery2dImmutableTest, Case1) {
  int matrix[5][5] = {{3, 0, 1, 4, 2}, {5, 6, 3, 2, 1}, {1, 2, 0, 1, 5}, {4, 1, 0, 1, 7}, {1, 0, 3, 0, 5}};
  int* ptr[5];
  for (int i = 0; i < 5; i++) {
    ptr[i] = matrix[i];
  }
  int matrixColSize[5] = {5, 5, 5, 5, 5};
  NumMatrix* obj = numMatrixCreate(ptr, 5, matrixColSize);
  ASSERT_EQ(numMatrixSumRegion(obj, 2, 1, 4, 3), 8);
  ASSERT_EQ(numMatrixSumRegion(obj, 1, 1, 2, 2), 11);
  ASSERT_EQ(numMatrixSumRegion(obj, 1, 2, 2, 4), 12);
  numMatrixFree(obj);
}
