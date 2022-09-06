// Palindrome Permutation: Given a string, write a function to check if it is a
// permutation of a palindrome. A palindrome is a word or phrase that is the
// same forwards and backwards. A permutation is a rearrangement of letters. The
// palindrome does not need to be limited to just dictionary words.

#include <iostream>
#include <string>
#include <unordered_map>

bool IsPalindromePermutation(std::string str) {
  std::unordered_map<char, int> chars;
  for (const auto elem : str) {
    if (chars.contains(elem)) {
      chars[elem] += 1;
    } else {
      chars[elem] = 1;
    }
  }
  bool one_odd{false};
  for (const auto [elem, count] : chars) {
    if (count % 2 != 0) {
      if (one_odd) {
        return false;
      }
      one_odd = true;
    }
  }
  return true;
}

int main() {
  std::cout << IsPalindromePermutation("aab") << std::endl;
  std::cout << IsPalindromePermutation("aabb") << std::endl;
  std::cout << IsPalindromePermutation("ccvvbbaas") << std::endl;
  std::cout << IsPalindromePermutation("aabbccd") << std::endl;
  std::cout << IsPalindromePermutation("aabc") << std::endl;
  std::cout << IsPalindromePermutation("aabcbt") << std::endl;

  return 0;
}