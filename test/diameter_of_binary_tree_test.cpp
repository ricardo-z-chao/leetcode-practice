extern "C" {
#include "leetcode/diameter_of_binary_tree.h"
}

#include <vector>

#include "gtest/gtest.h"

#define INCLUDE_UTILS
#ifdef INCLUDE_UTILS
  #include "utils/binary_tree_utils.h"
#endif

struct TestParam {
  std::vector<int> input;
  int expected;
};

class DiameterOfBinaryTreeTest : public ::testing::TestWithParam<TestParam> {
  void SetUp() override {}

  void TearDown() override {}
};

TEST_P(DiameterOfBinaryTreeTest, Default) {
  TestParam param = GetParam();
  struct TreeNode* root = BinaryTreeUtils::createTreeFromArray(param.input);
  int result = diameterOfBinaryTree(root);
  EXPECT_EQ(result, param.expected);
  BinaryTreeUtils::freeTree(root);
}

INSTANTIATE_TEST_SUITE_P(DiameterOfBinaryTreeDataSet,
                         DiameterOfBinaryTreeTest,
                         ::testing::Values(TestParam{{1, 2, 3, 4, 5}, 3}),
                         [](const ::testing::TestParamInfo<DiameterOfBinaryTreeTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
