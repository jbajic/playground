#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "structures/list/list.hpp"

using testing::ElementsAre;

TEST(TestList, ListTestPush) {
  {
    ladida::structures::List<int> list;
    EXPECT_NO_THROW(list.PushFront(1));
    EXPECT_NO_THROW(list.PushFront(2));
    EXPECT_NO_THROW(list.PushFront(3));
    EXPECT_EQ(list.Size(), 3);
    EXPECT_THAT(list, ElementsAre(3, 2, 1));
  }
  {
    ladida::structures::List<int> list;
    EXPECT_NO_THROW(list.PushBack(1));
    EXPECT_NO_THROW(list.PushBack(2));
    EXPECT_NO_THROW(list.PushBack(3));
    EXPECT_EQ(list.Size(), 3);
    EXPECT_THAT(list, ElementsAre(1, 2, 3));
  }
  {
    ladida::structures::List<int> list;
    EXPECT_NO_THROW(list.PushBack(1));
    EXPECT_NO_THROW(list.PushBack(2));
    EXPECT_NO_THROW(list.PushBack(3));
    EXPECT_NO_THROW(list.PushFront(0));
    EXPECT_NO_THROW(list.PushFront(-1));
    EXPECT_EQ(list.Size(), 5);
    EXPECT_THAT(list, ElementsAre(-1, 0, 1, 2, 3));
  }
}

TEST(TestList, ListTestPushAndPop) {
  {
    ladida::structures::List<int> list;
    EXPECT_NO_THROW(list.PushFront(1));
    EXPECT_NO_THROW(list.PushFront(2));
    EXPECT_NO_THROW(list.PushFront(3));
    EXPECT_NO_THROW(list.PushFront(4));
    EXPECT_EQ(list.PopBack(), 4);
    EXPECT_EQ(list.PopBack(), 3);
    EXPECT_EQ(list.Size(), 2);
    EXPECT_THAT(list, ElementsAre(2, 1));
  }
  {
    ladida::structures::List<int> list;
    EXPECT_NO_THROW(list.PushFront(1));
    EXPECT_NO_THROW(list.PushFront(2));
    EXPECT_NO_THROW(list.PushFront(3));
    EXPECT_NO_THROW(list.PushFront(4));
    EXPECT_EQ(list.PopFront(), 1);
    EXPECT_EQ(list.PopFront(), 2);
    EXPECT_EQ(list.Size(), 2);
    EXPECT_THAT(list, ElementsAre(4, 3));
  }
}
