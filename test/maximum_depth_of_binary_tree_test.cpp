extern "C" {
#include "leetcode/maximum_depth_of_binary_tree.h"
}

#include "gtest/gtest.h"

#define INCLUDE_UTILS
#ifdef INCLUDE_UTILS
  #include "utils/binary_tree_utils.h"
#endif

#include <vector>

struct TestParam {
  std::vector<int> input;
  int expected;
};

class MaximumDepthOfBinaryTreeTest : public ::testing::TestWithParam<TestParam> {
 protected:
  void TearDown() override {}
};

TEST_P(MaximumDepthOfBinaryTreeTest, Default) {
  TestParam param = GetParam();
  struct TreeNode* root = createTreeFromArray(param.input);
  int result = maxDepth(root);
  EXPECT_EQ(result, param.expected);
  freeTree(root);
}

INSTANTIATE_TEST_SUITE_P(MaximumDepthOfBinaryTreeDataSet,
                         MaximumDepthOfBinaryTreeTest,
                         ::testing::Values(TestParam{{3, 9, 20, -1, -1, 15, 7}, 3}),
                         [](const ::testing::TestParamInfo<MaximumDepthOfBinaryTreeTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
