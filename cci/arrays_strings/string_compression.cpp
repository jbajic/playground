#include <iostream>
#include <string>

std::string CompressString(std::string str) {
  std::string compressed_str;
  for (size_t i = 0; i < str.size(); ++i) {
    int local_count = 1;
    while (i < str.size() - 1 && str[i] == str[i + 1]) {
      ++local_count;
      ++i;
    }
    compressed_str.append(str[i] + std::to_string(local_count));
  }
  if (compressed_str.size() < str.size()) {
    return compressed_str;
  }
  std::cout << compressed_str << std::endl;
  return str;
}

int main() {
  std::cout << CompressString("abcdefg") << std::endl;
  std::cout << CompressString("abcdefgg") << std::endl;
  std::cout << CompressString("aaaaaaaaa") << std::endl;
  std::cout << CompressString("aaaaaaaaab") << std::endl;
  std::cout << CompressString("aaaaaaaaabccdd") << std::endl;
  std::cout << CompressString("abbccccddddeeeeee") << std::endl;
  return 0;
}
