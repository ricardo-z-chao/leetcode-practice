extern "C" {
#include "leetcode/range_sum_query_immutable.h"
}

#include "gtest/gtest.h"

class RangeSumQueryImmutableTest : public ::testing::Test {};

TEST_F(RangeSumQueryImmutableTest, Case1) {
  int* nums = new int[6]{-2, 0, 3, -5, 2, -1};
  NumArray* obj = numArrayCreate(nums, 6);
  ASSERT_EQ(numArraySumRange(obj, 0, 2), 1);
  ASSERT_EQ(numArraySumRange(obj, 2, 5), -1);
  ASSERT_EQ(numArraySumRange(obj, 0, 5), -3);
  numArrayFree(obj);
}
