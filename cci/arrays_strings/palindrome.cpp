// Palindrome Permutation: Given a string, write a function to check if it is a
// permutation of a palindrome. A palindrome is a word or phrase that is the
// same forwards and backwards. A permutation is a rearrangement of letters. The
// palindrome does not need to be limited to just dictionary words.

#include <iostream>
#include <string>
#include <unordered_map>

bool IsPalindromePermutation(std::string str) {
  int count_odd{0};
  std::unordered_map<char, int> chars;
  for (const auto elem : str) {
    if (chars.contains(elem)) {
      chars[elem] += 1;
    } else {
      chars[elem] = 1;
    }
    if (chars[elem] % 2 == 0) {
      count_odd -= 1;
    } else {
      count_odd += 1;
    }
  }
  return count_odd <= 1;
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