#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <type_traits>
#include <vector>

template <typename T>
class MatrixT {
 private:
  int rows, cols;
  std::vector<std::vector<T>> data;
  static auto clean(std::string text) -> std::string;

  static_assert(std::is_arithmetic_v<T>,
                "Matrix only supports arithmetic types");

 public:
  // Constructor
  MatrixT(int row, int col);

  // Accessors
  void set(int row, int col, T val);
  [[nodiscard]] auto get(int row, int col) const -> T;
  [[nodiscard]] auto getRows() const -> int { return rows; }
  [[nodiscard]] auto getCols() const -> int { return cols; }

  // For File I/O
  void writeToFile(const std::string& filename) const;
  static auto readFromFile(const std::string& filename) -> MatrixT<T>;

  // For Math Operations
  auto operator+(const MatrixT& other) const -> MatrixT;
  auto operator-(const MatrixT& other) const -> MatrixT;
  auto operator*(T scalar) const -> MatrixT;
  auto operator*(const MatrixT& other) const -> MatrixT;

  // For Display
  void display() const;
};

#include "matrix.tpp"

// Alias for backward compatibility
using Matrix = MatrixT<double>;

#endif
