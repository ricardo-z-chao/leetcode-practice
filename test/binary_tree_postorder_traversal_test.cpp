extern "C" {
#include "leetcode/binary_tree_postorder_traversal.h"
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

class BinaryTreePostorderTraversalTest : public ::testing::TestWithParam<TestParam> {
 protected:
  int* result;
  int returnSize;

  void TearDown() override {
    free(result);
  }
};

TEST_P(BinaryTreePostorderTraversalTest, Default) {
  TestParam param = GetParam();
  struct TreeNode* root = createTreeFromArray(param.input);
  result = postorderTraversal(root, &returnSize);
  EXPECT_EQ(treeToVector(result, returnSize), param.expected);
  freeTree(root);
}

INSTANTIATE_TEST_SUITE_P(BinaryTreePostorderTraversalDataSet,
                         BinaryTreePostorderTraversalTest,
                         ::testing::Values(TestParam{{1, 2, 3, 4, 5, NULL, 8, NULL, NULL, 6, 7, 9},
                                                     {4, 6, 7, 5, 2, 9, 8, 3, 1}}),
                         [](const ::testing::TestParamInfo<BinaryTreePostorderTraversalTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
