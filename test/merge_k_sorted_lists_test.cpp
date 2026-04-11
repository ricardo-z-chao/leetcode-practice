extern "C" {
#include "leetcode/merge_k_sorted_lists.h"
}

#include <vector>

#define INCLUDE_UTILS
#ifdef INCLUDE_UTILS
  #include "utils/linked_list_utils.h"
#endif

#include "gtest/gtest.h"

struct TestParam {
  std::vector<std::vector<int>> lists;
  std::vector<int> expected;
};

class MergeKSortedListsTest : public ::testing::TestWithParam<TestParam> {
 protected:
  struct ListNode* result;

  void TearDown() override {
    freeList(result);
  }
};

TEST_P(MergeKSortedListsTest, Default) {
  TestParam param = GetParam();
  int k = param.lists.size();
  struct ListNode** lists = (struct ListNode**)malloc(k * sizeof(struct ListNode*));
  for (int i = 0; i < k; i++) {
    lists[i] = createListFromArray(param.lists[i]);
  }
  result = mergeKLists(lists, k);
  EXPECT_EQ(listToVector(result), param.expected);
}

INSTANTIATE_TEST_SUITE_P(MergeKSortedListsDataSet,
                         MergeKSortedListsTest,
                         ::testing::Values(TestParam{{{1, 4, 5}, {1, 3, 4}, {2, 6}}, {1, 1, 2, 3, 4, 4, 5, 6}}),
                         [](const ::testing::TestParamInfo<MergeKSortedListsTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
