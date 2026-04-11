extern "C" {
#include "leetcode/merge_two_sorted_lists.h"
}

#include <vector>

#define INCLUDE_UTILS
#ifdef INCLUDE_UTILS
  #include "utils/linked_list_utils.h"
#endif

#include "gtest/gtest.h"

struct TestParam {
  std::vector<int> l1;
  std::vector<int> l2;
  std::vector<int> expected;
};

class MergeTwoSortedListsTest : public ::testing::TestWithParam<TestParam> {
 protected:
  struct ListNode* result;

  void TearDown() override {
    freeList(result);
  }
};


TEST_P(MergeTwoSortedListsTest, Default) {
  TestParam param = GetParam();
  struct ListNode* list1 = createListFromArray(param.l1);
  struct ListNode* list2 = createListFromArray(param.l2);
  result = mergeTwoLists(list1, list2);
  EXPECT_EQ(listToVector(result), param.expected);
}

INSTANTIATE_TEST_SUITE_P(MergeTwoSortedListsDataSet,
                         MergeTwoSortedListsTest,
                         ::testing::Values(TestParam{{1, 2, 4}, {1, 3, 4}, {1, 1, 2, 3, 4, 4}}),
                         [](const ::testing::TestParamInfo<MergeTwoSortedListsTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
