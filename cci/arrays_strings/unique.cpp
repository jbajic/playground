// Is Unique: Implement an algorithm to determine if a string has all unique
// characters. What if you cannot use additional data structures?

#include <array>
#include <iostream>
#include <string>

bool IsUnique(std::string str) {
  std::array<char, 128> chars{0};
  for (auto elem : str) {
    if (chars[elem] == 1) {
      return false;
    }
    chars[elem] = 1;
  }
  return true;
}

int main() {
  std::cout << IsUnique("abc") << std::endl;
  std::cout << IsUnique("abcdefghijkl123") << std::endl;
  std::cout << IsUnique("abca") << std::endl;
  std::cout << IsUnique("abcdefghijkl123e") << std::endl;
  return 0;
}