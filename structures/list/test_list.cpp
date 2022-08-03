#include <gtest/gtest.h>

#include "structures/list/list.hpp"

TEST(TestList, ListTestPush) {
  EXPECT_TRUE(true);
  {
    ladida::structures::List<int> list;
    EXPECT_NO_THROW(list.PushFront(1));
    EXPECT_NO_THROW(list.PushFront(2));
    EXPECT_NO_THROW(list.PushFront(3));
  }
  {
    ladida::structures::List<int> list;
    EXPECT_NO_THROW(list.PushBack(1));
    EXPECT_NO_THROW(list.PushBack(2));
    EXPECT_NO_THROW(list.PushBack(3));
  }
}

TEST(TestList, ListTestPushAndPop) {
  EXPECT_TRUE(true);
  {
    ladida::structures::List<int> list;
    list.PushFront(1);
    EXPECT_NO_THROW(list.PushFront(2));
    EXPECT_NO_THROW(list.PushFront(3));
  }
  {
    ladida::structures::List<int> list;
    EXPECT_NO_THROW(list.PushBack(1));
    EXPECT_NO_THROW(list.PushBack(2));
    EXPECT_NO_THROW(list.PushBack(3));
  }
}
