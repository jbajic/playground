#include <gtest/gtest.h>

#include "structures/list/list.hpp"

TEST(TestList, ListTestPush) {
  {
    static constexpr std::array expected_list{3, 2, 1};
    ladida::structures::List<int> list;
    EXPECT_NO_THROW(list.PushFront(1));
    EXPECT_NO_THROW(list.PushFront(2));
    EXPECT_NO_THROW(list.PushFront(3));
    EXPECT_EQ(list.Size(), 3);
    size_t counter{0};
    for (const auto &elem : list) {
      EXPECT_EQ(elem, expected_list[counter++]);
    }
  }
  {
    static constexpr std::array expected_list{1, 2, 3};
    ladida::structures::List<int> list;
    EXPECT_NO_THROW(list.PushBack(1));
    EXPECT_NO_THROW(list.PushBack(2));
    EXPECT_NO_THROW(list.PushBack(3));
    EXPECT_EQ(list.Size(), 3);
    size_t counter{0};
    for (const auto &elem : list) {
      EXPECT_EQ(elem, expected_list[counter++]);
    }
  }
  {
    static constexpr std::array expected_list{-1, 0, 1, 2, 3};
    ladida::structures::List<int> list;
    EXPECT_NO_THROW(list.PushBack(1));
    EXPECT_NO_THROW(list.PushBack(2));
    EXPECT_NO_THROW(list.PushBack(3));
    EXPECT_NO_THROW(list.PushFront(0));
    EXPECT_NO_THROW(list.PushFront(-1));
    EXPECT_EQ(list.Size(), 5);
    size_t counter{0};
    for (const auto &elem : list) {
      EXPECT_EQ(elem, expected_list[counter++]);
    }
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
  }
}
