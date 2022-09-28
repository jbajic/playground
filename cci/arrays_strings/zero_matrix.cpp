// Zero Matrix: Write an algorithm such that if an element in an MxN matrix is
// 0, its entire row and column are set to 0

#include <iostream>
#include <vector>
#include <set>

void ZerofiyRow(auto &matrix, int row, int column_size) {
  for (int i{0}; i < column_size; ++i) {
    matrix[row][i] = 0;
  }
}

void ZerofiyColumn(auto &matrix, int column, int row_size) {
  for (int i{0}; i < row_size; ++i) {
    matrix[i][column] = 0;
  }
}

void ZerofyMatrix(std::vector<std::vector<int>> &matrix) {
  std::set<int> rows;
  std::set<int> columns;
  for (int i{0}; i < matrix.size(); ++i) {
    for (int j{0}; j < matrix[i].size(); ++j) {
      if (!rows.contains(i) && !columns.contains(j) && matrix[i][j] == 0) {
        ZerofiyRow(matrix, i, matrix[0].size());
        ZerofiyColumn(matrix, j, matrix.size());
        rows.insert(i);
        columns.insert(j);
      }
    }
  }
}

void PrintMatrix(const auto &matrix) {
  for (const auto row : matrix) {
    for (const auto elem : row) {
      std::cout << elem << ", ";
    }
    std::cout << std::endl;
  }
}

int main() {
  std::vector<std::vector<int>> matrix{
      {1, 2, 3}, {4, 5, 0}, {7, 8, 9}, {3, 2, 1}, {6, 5, 4}};
  PrintMatrix(matrix);
  ZerofyMatrix(matrix);
  std::cout << std::endl;
  PrintMatrix(matrix);

  return 0;
}
