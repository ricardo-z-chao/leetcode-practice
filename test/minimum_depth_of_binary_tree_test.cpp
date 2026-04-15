extern "C" {
#include "leetcode/minimum_depth_of_binary_tree.h"
}

#include <vector>

#define INCLUDE_UTILS
#ifdef INCLUDE_UTILS
  #include "utils/binary_tree_utils.h"
#endif

#include "gtest/gtest.h"

struct TestParam {
  std::vector<int> input;
  int expected;
};

class MinimumDepthOfBinaryTreeTest : public ::testing::TestWithParam<TestParam> {
 protected:
  void TearDown() override {}
};

TEST_P(MinimumDepthOfBinaryTreeTest, Cases) {
  TestParam param = GetParam();
  struct TreeNode* root = createTreeFromArray(param.input);
  int result = minDepth(root);
  EXPECT_EQ(result, param.expected);
  freeTree(root);
}

INSTANTIATE_TEST_SUITE_P(MinimumDepthOfBinaryTreeDataSet,
                         MinimumDepthOfBinaryTreeTest,
                         ::testing::Values(TestParam{{3, 9, 20, NULL, NULL, 15, 7}, 2}),
                         [](const ::testing::TestParamInfo<MinimumDepthOfBinaryTreeTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
