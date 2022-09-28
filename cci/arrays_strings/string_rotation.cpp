// Assume you have a method `isSubstringwhich` checks if one word
// is a substring of another. Given two strings, sl and s2, write code to check
// if s2 is a rotation of sl using only one call to isSubstring
// (e.g.,"waterbottle" is a rotation of"erbottlewat").

#include <iostream>
#include <string>

// Check if s2 is substring of s1
bool IsSubstringRotation(std::string s1, std::string s2) {
  if (s2.size() > s1.size()) {
    return false;
  }
  std::cout << "pass" << std::endl;

  for (size_t i{0}; i < s1.size(); ++i) {
    if (s1[i] == s2[0]) {
      // continue checking
      auto new_i = i + 1;
      if (new_i == s1.size()) {
        new_i = 0;
      }
      bool substring_found{true};
      for (size_t j{1}; j < s2.size(); ++j) {
        if (s1[new_i] != s2[j]) {
          substring_found = false;
          break;
        }
        if (++new_i == s1.size()) {
          new_i = 0;
        }
      }
      if (substring_found) {
        return true;
      }
    }
  }
  return false;
}

int main() {
  std::cout << static_cast<int>(
                   IsSubstringRotation("waterbottle", "erbottlewat"))
            << std::endl;
  return 0;
}