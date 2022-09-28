// Rotate Matrix: Given an image represented by an NxN matrix, where each pixel
// in the image is 4 bytes, write a method to rotate the image by 90 degrees.
// Can you do this in place?

#include <iostream>
// 1 2 3 4 5                21 16 11 6 1
// 6 7 8 9 10        =>     22 17 12 7 2
// 11 12 13 14 15           23 18 13 8 3
// 16 17 18 19 20           24 19 14 9 4
// 21 22 23 24 25          25 20 15 10 5
//
// 1 2 3      7 4 1
// 4 5 6 =>   8 5 2
// 7 8 9      9 6 3
//
// i,j
// 0,0 => 0,2
// 0,1 => 1,2
// 0,2 => 2,2
//
// 1,0 => 0,1
// 1,1 => 1,1
// 1,2 => 2,1
//
// 2,0 => 0,0
// 2,1 => 1,0
// 2,2 => 2,0

template <size_t n>
void RotateMatrix(int (&matrix)[n][n]) {
  static constexpr auto m{n - 1};
  for (size_t i = 0; i < m; ++i) {
    size_t temp = matrix[0][i];           // 1
    matrix[0][i] = matrix[m - i][0];      // 2
    matrix[m - i][0] = matrix[m][m - i];  // 3
    matrix[m][m - i] = matrix[i][m];      // 4
    matrix[i][m] = temp;                  // 5
  }
}

int main() {
  int m1[][3]{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  RotateMatrix<3>(m1);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      std::cout << m1[i][j] << ", ";
    }
    std::cout << std::endl;
  }

  return 0;
}
