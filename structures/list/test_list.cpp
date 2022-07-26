#include "list.hpp"
#include "structures/list/list.hpp"

#include <gtest/gtest.h>

TEST(List, CreateList) {
    ASSERT_NO_THROladida::structures::List<int> l1;
    ladida::structures::List<std::string> l2;
    ladida::structures::List<int> l3;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  memgraph::logging::RedirectToStderr();
  spdlog::set_level(spdlog::level::trace);
  return RUN_ALL_TESTS();
}
