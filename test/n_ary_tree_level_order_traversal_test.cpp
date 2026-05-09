extern "C" {
#include "leetcode/n_ary_tree_level_order_traversal.h"
}

#include <vector>

#define INCLUDE_UTILS
#ifdef INCLUDE_UTILS
  #include "utils/multi_tree_utils.h"
#endif

#include "gtest/gtest.h"

struct TestParam {
  std::vector<int> input;
  std::vector<std::vector<int>> expected;
};

class NAryTreeLevelOrderTraversalTest : public ::testing::TestWithParam<TestParam> {
  void SetUp() override {}

  void TearDown() override {}
};

TEST_P(NAryTreeLevelOrderTraversalTest, Default) {
  TestParam param = GetParam();
  struct Node* root = MultiTreeUtils::createTreeFromArray(param.input);
  int returnSize = 0;
  int* returnColumnSizes = nullptr;
  int** result = levelOrder(root, &returnSize, &returnColumnSizes);

  std::vector<std::vector<int>> actual;
  for (int i = 0; i < returnSize; i++) {
    std::vector<int> level;
    for (int j = 0; j < returnColumnSizes[i]; j++) {
      level.push_back(result[i][j]);
    }
    actual.push_back(level);
  }

  EXPECT_EQ(actual, param.expected);
  MultiTreeUtils::freeTree(root);
  free(returnColumnSizes);
  for (int i = 0; i < returnSize; i++) {
    free(result[i]);
  }
  free(result);
}

INSTANTIATE_TEST_SUITE_P(NAryTreeLevelOrderTraversalDataSet,
                         NAryTreeLevelOrderTraversalTest,
                         ::testing::Values(TestParam{
                           {1, NULL, 2,    3,    4,  5,    NULL, NULL, 6,  7,    NULL, 8, NULL,
                            9, 10,   NULL, NULL, 11, NULL, 12,   NULL, 13, NULL, NULL, 14},
                           {{1}, {2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13}, {14}}}),
                         [](const ::testing::TestParamInfo<NAryTreeLevelOrderTraversalTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
