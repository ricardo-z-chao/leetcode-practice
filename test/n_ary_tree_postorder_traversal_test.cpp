extern "C" {
#include "leetcode/n_ary_tree_postorder_traversal.h"
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

class NAryTreePostorderTraversalTest : public ::testing::TestWithParam<TestParam> {
  void SetUp() override {}

  void TearDown() override {}
};

TEST_P(NAryTreePostorderTraversalTest, Default) {
  TestParam param = GetParam();
  struct Node* root = MultiTreeUtils::createTreeFromArray(param.input);
  int returnSize = 0;
  int* result = postorder(root, &returnSize);
  std::vector<int> actual = MultiTreeUtils::treeToVector(result, returnSize);
  EXPECT_EQ(actual, param.expected);
  MultiTreeUtils::freeTree(root);
  free(result);
}

INSTANTIATE_TEST_SUITE_P(NAryTreePostorderTraversalDataSet,
                         NAryTreePostorderTraversalTest,
                         ::testing::Values(TestParam{
                           {1, NULL, 2,    3,    4,  5,    NULL, NULL, 6,  7,    NULL, 8, NULL,
                            9, 10,   NULL, NULL, 11, NULL, 12,   NULL, 13, NULL, NULL, 14},
                           {2, 6, 14, 11, 7, 3, 12, 8, 4, 13, 9, 10, 5, 1}}),
                         [](const ::testing::TestParamInfo<NAryTreePostorderTraversalTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
