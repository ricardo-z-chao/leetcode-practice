extern "C" {
#include "leetcode/lru_cache.h"
}

#include "gtest/gtest.h"

class LruCacheTest : public ::testing::Test {
 protected:
  LRUCache* lRUCache = nullptr;

  void SetUp() override {}

  void TearDown() override {
    lRUCacheFree(lRUCache);
  }
};

TEST_F(LruCacheTest, Case1) {
  lRUCache = lRUCacheCreate(2);
  lRUCachePut(lRUCache, 1, 1);
  lRUCachePut(lRUCache, 2, 2);
  ASSERT_EQ(1, lRUCacheGet(lRUCache, 1));
  lRUCachePut(lRUCache, 3, 3);
  ASSERT_EQ(-1, lRUCacheGet(lRUCache, 2));
  lRUCachePut(lRUCache, 4, 4);
  ASSERT_EQ(-1, lRUCacheGet(lRUCache, 1));
  ASSERT_EQ(3, lRUCacheGet(lRUCache, 3));
  ASSERT_EQ(4, lRUCacheGet(lRUCache, 4));
}
