// URLify: Write a method to replace all spaces in a string with '%20'. You may
// assume that the string has sufficient space at the end to hold the additional
// characters, and that you are given the "true" length of the string. (Note: If
// implementing in Java, please use a character array so that you can perform
// this operation in place.)
#include <iostream>
#include <string>

std::string URLify(std::string str) {
  std::string ret;
  bool is_space{false};
  for (const auto elem : str) {
    if (elem != ' ') {
      ret.push_back(elem);
      is_space = false;
    } else {
      if (is_space == true) {
        continue;
      } else {
        ret.append("%20");
        is_space = true;
      }
    }
  }
  return ret;
}

int main() {
  std::cout << URLify("abcdedfg") << std::endl;
  std::cout << URLify("A B       C D    ") << std::endl;
  std::cout << URLify("A B C D") << std::endl;
  return 0;
}