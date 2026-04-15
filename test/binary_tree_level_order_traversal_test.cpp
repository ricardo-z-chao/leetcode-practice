extern "C" {
#include "leetcode/binary_tree_level_order_traversal.h"
}

#include <vector>
#include <cstdlib>

#include "gtest/gtest.h"

#define INCLUDE_UTILS
#ifdef INCLUDE_UTILS
  #include "utils/binary_tree_utils.h"
#endif

struct TestParam {
  std::vector<int> input;
  std::vector<std::vector<int>> expected;
};

class BinaryTreeLevelOrderTraversalTest : public ::testing::TestWithParam<TestParam> {
 protected:
  void TearDown() override {
    // Cleanup if needed
  }
};

TEST_P(BinaryTreeLevelOrderTraversalTest, LevelOrderTraversal) {
  TestParam param = GetParam();

  struct TreeNode* root = createTreeFromArray(param.input);
  ASSERT_NE(root, nullptr);

  int returnSize = 0;
  int* returnColumnSizes = nullptr;
  int** result = levelOrder(root, &returnSize, &returnColumnSizes);

  ASSERT_EQ(returnSize, static_cast<int>(param.expected.size()));

  for (int i = 0; i < returnSize; i++) {
    ASSERT_EQ(returnColumnSizes[i], static_cast<int>(param.expected[i].size()));
    for (int j = 0; j < returnColumnSizes[i]; j++) {
      EXPECT_EQ(result[i][j], param.expected[i][j]);
    }
  }

  // Free allocated memory
  for (int i = 0; i < returnSize; i++) {
    free(result[i]);
  }
  free(result);
  free(returnColumnSizes);
  freeTree(root);
}

std::vector<TestParam> GetTestCases() {
  return {
    {std::vector<int>{3, 9, 20, NULL, NULL, 15, 7}, std::vector<std::vector<int>>{{3}, {9, 20}, {15, 7}}},
  };
}

INSTANTIATE_TEST_SUITE_P(BinaryTreeLevelOrderTraversalDataSet,
                         BinaryTreeLevelOrderTraversalTest,
                         ::testing::ValuesIn(GetTestCases()),
                         [](const ::testing::TestParamInfo<BinaryTreeLevelOrderTraversalTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
