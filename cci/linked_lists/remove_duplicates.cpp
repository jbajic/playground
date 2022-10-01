// Write code to remove duplicates from an unsorted linked list.

#include <iostream>
#include <list>
#include <map>


// Using map
void RemoveDuplicates(std::list<int> &l) {
    std::map<int, int> elems;
    for(const auto &elem: l) {
        if(elems.contains(elem)) {
            elems[elem]++;
        } else {
          elems[elem] = 1;
        }
    }
    for(auto it = l.begin(); it != l.end();) {
        if(elems[*it] > 1) {
            elems[*it] -= 1;
            it = l.erase(it);
        } else {
          ++it;
        }
    }
}

void PrintList(std::list<int> &l) {
  for (const auto &elem : l) {
    std::cout << elem << ", ";
  }
  std::cout << std::endl;
}

int main() {
  std::list<int> l1{1, 2, 3};
  std::list<int> l2{1, 2, 3, 4, 5, 6};
  std::list<int> l3{1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
  std::list<int> l4{1, 2, 1, 3, 4, 2, 5, 6, 3, 1, 3};

  std::cout << "Before removing duplicates:" << std::endl;
  PrintList(l1);
  PrintList(l2);
  PrintList(l3);
  PrintList(l4);

  RemoveDuplicates(l1);
  RemoveDuplicates(l2);
  RemoveDuplicates(l3);
  RemoveDuplicates(l4);

  std::cout << "After removing duplicates:" << std::endl;
  PrintList(l1);
  PrintList(l2);
  PrintList(l3);
  PrintList(l4);
  return 0;
}
