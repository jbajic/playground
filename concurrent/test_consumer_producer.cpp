#include <gtest/gtest.h>

#include <iostream>
#include <thread>
#include <vector>

#include "concurrent/consumer_producer.hpp"

TEST(TestProducerConsumer, TestBasicAddPopInSingleThread) {
  Buffer<int64_t> buffer(10);
  for (int64_t i{0}; i < 10; ++i) {
    EXPECT_TRUE(buffer.Add(i));
  }
  for (int64_t i{0}; i < 10; ++i) {
    EXPECT_EQ(*buffer.Pop(), i);
  }
}

TEST(TestProducerConsumer, TwoThreads) {
  Buffer<int64_t> buffer(10);
  const auto producer = [&buffer]() {
    for (int64_t i{0}; i < 10; ++i) {
      const auto res = buffer.Add(i);
      std::cerr << "Adding " << i << ": " << std::boolalpha << res << std::endl;
    }
  };
  const auto consumer = [&buffer]() {
    for (int64_t i{0}; i < 10; ++i) {
      if (const auto data = buffer.Pop(); data) {
        std::cerr << "Popping " << *data << std::endl;
        EXPECT_TRUE(*data >= 0 && *data < 10);
      } else {
        std::cerr << "No data to pop!" << std::endl;
      }
    }
  };
  std::vector<std::jthread> producers;
  std::vector<std::jthread> consumers;
  const auto processor_count = std::thread::hardware_concurrency();

  ASSERT_TRUE(processor_count > 0) << "Concurrency not defined!";
  for (size_t i{0}; i < processor_count / 2; ++i) {
    std::cerr << "Starting " << i << std::endl;
    producers.push_back(std::jthread(consumer));
    producers.push_back(std::jthread(producer));
  }
}
