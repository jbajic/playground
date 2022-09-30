// Check Permutation: Given two strings, write a method to decide if one is a
// permutation of the other
#include <array>
#include <iostream>
#include <string>

bool IsPermutation(std::string str1, std::string str2) {
  if (str1.size() != str2.size()) {
    return false;
  }
  std::array<char, 128> elems{0};
  for (const auto c : str1) {
    elems[c] += 1;
  }
  for (const auto c : str2) {
    if (elems[c] == 0) {
      return false;
    }
    elems[c] -= 1;
  }
  return true;
}

int main() {
  std::cout << IsPermutation("abc", "cba") << std::endl;
  std::cout << IsPermutation("abcefghijk", "abcghfkije") << std::endl;
  std::cout << IsPermutation("aaa", "aab") << std::endl;
  std::cout << IsPermutation("abc", "cbad") << std::endl;
  std::cout << IsPermutation("abce", "cbad") << std::endl;
  return 0;
}
