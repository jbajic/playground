// One Away: There are three types of edits that can be performed on strings:
// insert a character, remove a character, or replace a character. Given two
// strings, write a function to check if they are one edit (or zero edits) away.

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

bool IsOneEditAway(std::string str1, std::string str2) {
  size_t i{0};
  size_t j{0};
  bool mistake{false};
  bool size{false};  // do we update or add/remove
  const auto diff = std::abs(static_cast<int>(str1.size() - str2.size()));
  if (diff > 1) {
    return false;
  } else if (diff == 0) {
    size = true;
  }
  while (i < str1.size() && j < str2.size()) {
    if (str1[i] != str2[j] && mistake) {
      return false;
    } else if (str1[i] != str2[j]) {
      mistake = true;
      if (!size) {
        if (str1.size() > str2.size()) {
          ++i;
          continue;
        } else {
          ++j;
          continue;
        }
      }
    }
    ++i;
    ++j;
  }
  return true;
}

int main() {
  std::cout << IsOneEditAway("abc", "abc") << std::endl;
  std::cout << IsOneEditAway("abc", "abcd") << std::endl;
  std::cout << IsOneEditAway("abc", "ab") << std::endl;
  std::cout << IsOneEditAway("aebc", "abc") << std::endl;
  std::cout << IsOneEditAway("abc", "bc") << std::endl;
  std::cout << IsOneEditAway("abc", "abcde") << std::endl;
  std::cout << IsOneEditAway("abc", "cba") << std::endl;
  std::cout << IsOneEditAway("abc", "cbad") << std::endl;
  return 0;
}