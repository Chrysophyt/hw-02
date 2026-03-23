#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <vector>

class Matrix {
 private:
  int rows, cols;
  std::vector<std::vector<double>> data;
  static auto clean(std::string text) -> std::string;

 public:
  // Constructor
  Matrix(int row, int col);

  // Accessors
  void set(int row, int col, double val);
  [[nodiscard]] auto get(int row, int col) const -> double;
  [[nodiscard]] auto getRows() const -> int { return rows; }
  [[nodiscard]] auto getCols() const -> int { return cols; }

  // For File I/O
  void writeToFile(const std::string& filename) const;
  static auto readFromFile(const std::string& filename) -> Matrix;

  // For Math Operations
  auto operator+(const Matrix& other) const -> Matrix;
  auto operator-(const Matrix& other) const -> Matrix;
  auto operator*(double scalar) const -> Matrix;
  auto operator*(const Matrix& other) const -> Matrix;

  // For Display
  void display() const;
};

#endif
