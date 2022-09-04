// Palindrome Permutation: Given a string, write a function to check if it is a
// permutation of a palindrome. A palindrome is a word or phrase that is the
// same forwards and backwards. A permutation is a rearrangement of letters. The
// palindrome does not need to be limited to just dictionary words.

#include <iostream>
#include <string>

bool IsPalindrome(std::string str1, std::string str2) {
  if (str1.size() != str2.size()) {
    return false;
  }
  int i = 0;
  int j = str1.size() - 1;
  while (i < str1.size()) {
    if (str1[i] != str2[j]) {
      return false;
    }
    ++i;
    --j;
  }
  return true;
}

int main() {
  std::cout << IsPalindrome("abc", "cba") << std::endl;
  std::cout << IsPalindrome("abc cba", "abc cba") << std::endl;
  std::cout << IsPalindrome("abcde fghi", "ihgf edcba") << std::endl;
  std::cout << IsPalindrome("abc", "bca") << std::endl;
  std::cout << IsPalindrome("abcde fghi", "ihgf edcab") << std::endl;

  return 0;
}