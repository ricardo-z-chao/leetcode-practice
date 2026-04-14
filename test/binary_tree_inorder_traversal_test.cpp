extern "C" {
#include "leetcode/binary_tree_inorder_traversal.h"
}

#include <vector>

#include "gtest/gtest.h"

#define INCLUDE_UTILS
#ifdef INCLUDE_UTILS
  #include "utils/binary_tree_utils.h"
#endif

struct TestParam {
  std::vector<int> input;
  std::vector<int> expected;
};

class BinaryTreeInorderTraversalTest : public ::testing::TestWithParam<TestParam> {
 protected:
  int* result;
  int returnSize;

  void TearDown() override {
    free(result);
  }
};

TEST_P(BinaryTreeInorderTraversalTest, Default) {
  TestParam param = GetParam();
  struct TreeNode* root = createTreeFromArray(param.input);
  result = inorderTraversal(root, &returnSize);
  EXPECT_EQ(treeToVector(result, returnSize), param.expected);
  freeTree(root);
}

INSTANTIATE_TEST_SUITE_P(BinaryTreeInorderTraversalDataSet,
                         BinaryTreeInorderTraversalTest,
                         ::testing::Values(TestParam{{1, 2, 3, 4, 5, NULL, 8, NULL, NULL, 6, 7, 9},
                                                     {4, 2, 6, 5, 7, 1, 3, 9, 8}}),
                         [](const ::testing::TestParamInfo<BinaryTreeInorderTraversalTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
