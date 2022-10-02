// Delete Middle Node: Implement an algorithm to delete a node in the middle
// (i.e., any node but the first and last node, not necessarily the exact
// middle) of a singly linked list, given only access to that node.
#include <iostream>
#include <list>

#include "cci/utils.hpp"

void DeleteMiddle(std::list<int>& l) {
    auto slow = l.begin();
    auto fast = l.begin();
    while(fast != l.end()) {
        if(++fast != l.end()) {
            ++fast;
        } else {
            break;
        }
        ++slow;
    }
    l.erase(slow);
}

int main() {
    std::list<int> l1{1,2,3};
    std::list<int> l2{1,2,3,4};
    std::list<int> l3{1,2,3,4,5,6,7,8,9};
    std::list<int> l4{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    PrintContainer(l1);
    PrintContainer(l2);

    DeleteMiddle(l1);
    DeleteMiddle(l2);

    PrintContainer(l1);
    PrintContainer(l2);

    return 0;
}
