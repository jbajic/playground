// Partition: Write code to partition a linked list around a value x, such that
// all nodes less than x come before all nodes greater than or equal to x. If x
// is contained within the list, the values of x only need to be after the
// elements less than x (see below). The partition element x can appear anywhere
// in the "right partition"; it does not need to appear between the left and
// right partitions.

#include <iostream>
#include <list>

#include "cci/utils.hpp"

// new list & doubly linked list
std::list<int> Partition(std::list<int> list, int partition_key) {
  std::list<int> partitioned;
  for (const auto& elem : list) {
    if (elem < partition_key) {
      partitioned.push_front(elem);
    } else {
      partitioned.push_back(elem);
    }
  }
  return partitioned;
}

// new list & single linked list
std::list<int> Partition2(std::list<int> list, int partition_key) {
  std::list<int> partitioned;
  for (const auto& elem : list) {
    if (elem < partition_key) {
      partitioned.push_back(elem);
    }
  }
  for (const auto& elem : list) {
    if (elem >= partition_key) {
      partitioned.push_back(elem);
    }
  }
  return partitioned;
}

// inplace
std::list<int> Partition3(std::list<int> list, int partition_key) {
  auto start_it = list.begin();
  auto end_it = std::prev(list.begin());
  while (std::distance(start_it, end_it) > 0) {
    if (*start_it >= partition_key && *end_it < partition_key) {
      std::swap(*start_it, *end_it);
      ++start_it;
      --end_it;
      continue;
    }
    if (*start_it < partition_key) {
      ++start_it;
    }
    if (*end_it >= partition_key) {
      --end_it;
    }
  }

  return list;
}

int main() {
  std::list<int> l1{4, 1, 78, 3, 5, 6, 3, 1};
  std::list<int> l2{1, 9, 2, 8, 3, 8, 4, 8, 5, 6, 7, 1, 2, 3};

  PrintContainer(l1);

  std::cout << "Solution 1:" << std::endl;
  PrintContainer(Partition(l1, 4));
  PrintContainer(Partition(l2, 5));
  std::cout << "Solution 2:" << std::endl;
  PrintContainer(Partition2(l1, 4));
  PrintContainer(Partition2(l2, 5));
  std::cout << "Solution 3:" << std::endl;
  PrintContainer(Partition3(l1, 4));
  PrintContainer(Partition3(l2, 5));
  return 0;
}
