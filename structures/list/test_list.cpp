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
    EXPECT_NO_THROW(list.PushBack(1));
    EXPECT_NO_THROW(list.PushBack(2));
    EXPECT_NO_THROW(list.PushBack(3));
    EXPECT_NO_THROW(list.PushBack(4));
    EXPECT_EQ(list.PopBack(), 4);
    EXPECT_EQ(list.PopBack(), 3);
    EXPECT_EQ(list.Size(), 2);
    EXPECT_THAT(list, ElementsAre(1, 2));
  }
  {
    ladida::structures::List<int> list;
    EXPECT_NO_THROW(list.PushFront(1));
    EXPECT_NO_THROW(list.PushFront(2));
    EXPECT_NO_THROW(list.PushFront(3));
    EXPECT_NO_THROW(list.PushFront(4));
    EXPECT_EQ(list.PopFront(), 4);
    EXPECT_EQ(list.PopFront(), 3);
    EXPECT_EQ(list.Size(), 2);
    EXPECT_THAT(list, ElementsAre(2, 1));
  }
  {
    ladida::structures::List<int> list;
    EXPECT_NO_THROW(list.PushBack(1));
    EXPECT_NO_THROW(list.PushBack(2));
    EXPECT_NO_THROW(list.PushBack(3));
    EXPECT_NO_THROW(list.PushBack(4));
    EXPECT_EQ(list.PopFront(), 1);
    EXPECT_EQ(list.PopBack(), 4);
    EXPECT_EQ(list.Size(), 2);
    EXPECT_THAT(list, ElementsAre(2, 3));
  }
}

TEST(TestList, ListTestIteration) {
  std::array expected{1, 2, 3, 4};
  ladida::structures::List<int> list;
  for (const auto elem : expected) {
    EXPECT_NO_THROW(list.PushBack(elem));
  }
  EXPECT_EQ(list.Size(), expected.size());
  EXPECT_THAT(list, ElementsAre(1, 2, 3, 4));

  {
    size_t counter{0};
    for (const auto elem : list) {
      EXPECT_EQ(elem, expected[counter++]);
    }
    EXPECT_EQ(counter, expected.size());
  }
  {
    size_t counter{0};
    for (auto it = list.begin(); it != list.end(); ++it) {
      EXPECT_EQ(*it, expected[counter++]);
    }
    EXPECT_EQ(counter, expected.size());
  }
}
TEST(TestList, ListTestReverseIteration) {
  std::array expected{1, 2, 3, 4};
  ladida::structures::List<int> list;
  for (const auto elem : expected) {
    EXPECT_NO_THROW(list.PushBack(elem));
  }
  EXPECT_EQ(list.Size(), expected.size());
  EXPECT_THAT(list, ElementsAre(1, 2, 3, 4));

  // Test reverse iteration
  {
    size_t counter{expected.size() - 1};
    for (auto it = list.rbegin(); it != list.rend(); ++it) {
      EXPECT_EQ(*it, expected[counter--]);
    }
    EXPECT_EQ(counter, 0);
  }
  {
    size_t counter{expected.size() - 1};
    for (auto it = list.rbegin(); it != list.rend(); ++it) {
      EXPECT_EQ(*it, expected[counter--]);
    }
    EXPECT_EQ(counter, 0);
  }
}
