extern "C" {
#include "leetcode/n_ary_tree_preorder_traversal.h"
}

#include <vector>

#define INCLUDE_UTILS
#ifdef INCLUDE_UTILS
  #include "utils/multi_tree_utils.h"
#endif

#include "gtest/gtest.h"

struct TestParam {
  std::vector<int> input;
  std::vector<int> expected;
};

class NAryTreePreorderTraversalTest : public ::testing::TestWithParam<TestParam> {
  void SetUp() override {}
  void TearDown() override {}
};

TEST_P(NAryTreePreorderTraversalTest, Default) {
  TestParam param = GetParam();
  struct Node* root = MultiTreeUtils::createTreeFromArray(param.input);
  int returnSize = 0;
  int* result = preorder(root, &returnSize);
  std::vector<int> actual = MultiTreeUtils::treeToVector(result, returnSize);
  EXPECT_EQ(actual, param.expected);
  MultiTreeUtils::freeTree(root);
  free(result);
}

INSTANTIATE_TEST_SUITE_P(NAryTreePreorderTraversalDataSet,
                         NAryTreePreorderTraversalTest,
                         ::testing::Values(TestParam{
                           {1, NULL, 2,    3,    4,  5,    NULL, NULL, 6,  7,    NULL, 8, NULL,
                            9, 10,   NULL, NULL, 11, NULL, 12,   NULL, 13, NULL, NULL, 14},
                           {1, 2, 3, 6, 7, 11, 14, 4, 8, 12, 5, 9, 13, 10}}),
                         [](const ::testing::TestParamInfo<NAryTreePreorderTraversalTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
