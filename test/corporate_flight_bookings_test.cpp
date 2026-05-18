extern "C" {
#include "leetcode/corporate_flight_bookings.h"
}

#include <stdlib.h>

#include <vector>

#include "gtest/gtest.h"

struct TestParam {
  int n;
  std::vector<std::vector<int>> bookings;
  std::vector<int> expected;
};

class CorporateFlightBookingsTest : public ::testing::TestWithParam<TestParam> {
 protected:
  TestParam param = GetParam();
  int** bookings;
  int* answer;

  void SetUp() override {
    bookings = reinterpret_cast<int**>(malloc(param.bookings.size() * sizeof(int*)));
    for (size_t i = 0; i < param.bookings.size(); i++) {
      bookings[i] = reinterpret_cast<int*>(malloc(3 * sizeof(int)));
      bookings[i][0] = param.bookings[i][0];
      bookings[i][1] = param.bookings[i][1];
      bookings[i][2] = param.bookings[i][2];
    }
  }

  void TearDown() override {}
};

TEST_P(CorporateFlightBookingsTest, Default) {
  int returnSize;
  int* result = corpFlightBookings(bookings, param.bookings.size(), NULL, param.n, &returnSize);
  for (int i = 0; i < returnSize; ++i) {
    ASSERT_EQ(result[i], param.expected[i]);
  }
}

INSTANTIATE_TEST_SUITE_P(CorporateFlightBookingsDataSet,
                         CorporateFlightBookingsTest,
                         ::testing::Values(TestParam{5, {{1, 2, 10}, {2, 3, 20}, {2, 5, 25}}, {10, 55, 45, 25, 25}}),
                         [](const ::testing::TestParamInfo<CorporateFlightBookingsTest::ParamType>& info) {
                           return "Case" + std::to_string(info.index + 1);
                         });
