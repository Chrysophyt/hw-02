#ifndef MATRIX_TPP
#define MATRIX_TPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

// Constructor
template <typename T>
MatrixT<T>::MatrixT(int row, int col)
    : rows(row), cols(col), data(row, std::vector<T>(col, T{})) {}

// Accessors
template <typename T>
void MatrixT<T>::set(int row, int col, T val) {
  data[row][col] = val;
}

template <typename T>
auto MatrixT<T>::get(int row, int col) const -> T {
  return data[row][col];
}

// Private string cleaner
template <typename T>
auto MatrixT<T>::clean(std::string text) -> std::string {
  // Boost::algorithm dependencies needed for this
  // NOLINTBEGIN(boost-use-ranges)
  text.erase(std::remove(text.begin(), text.end(), '['), text.end());
  text.erase(std::remove(text.begin(), text.end(), ']'), text.end());
  text.erase(std::remove(text.begin(), text.end(), ','), text.end());
  // NOLINTEND(boost-use-ranges)
  return text;
}

// Write to File
template <typename T>
void MatrixT<T>::writeToFile(const std::string& filename) const {
  std::ofstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file for writing.");
  }

  file << "[\n";
  for (int i = 0; i < rows; ++i) {
    file << "  [";
    for (int j = 0; j < cols; ++j) {
      file << data[i][j] << (j == cols - 1 ? "" : ", ");
    }
    file << "]" << (i == rows - 1 ? "" : ",\n");
  }
  file << "\n]";
  file.close();
}

// Read from File
template <typename T>
auto MatrixT<T>::readFromFile(const std::string& filename) -> MatrixT<T> {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file.");
  }

  std::vector<std::vector<T>> temp_data;
  std::string line;

  while (std::getline(file, line)) {
    if (line.find('[') != std::string::npos &&
        line.find_first_not_of(" []\n,") != std::string::npos) {
      std::vector<T> row;
      std::stringstream strings(clean(line));
      T val{};

      while (strings >> val) {
        row.push_back(val);
      }

      if (!strings.eof()) {
        throw std::runtime_error("Invalid character in matrix data.");
      }

      if (!row.empty()) {
        temp_data.push_back(row);
      }
    }
  }

  if (temp_data.empty()) {
    throw std::runtime_error("File is empty or invalid format.");
  }

  MatrixT<T> result(static_cast<int>(temp_data.size()),
                    static_cast<int>(temp_data[0].size()));
  result.data = temp_data;
  return result;
}

// Addition
template <typename T>
auto MatrixT<T>::operator+(const MatrixT<T>& other) const -> MatrixT<T> {
  if (rows != other.rows || cols != other.cols) {
    throw std::invalid_argument("Size mismatch for addition.");
  }

  MatrixT<T> res(rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      res.data[i][j] = data[i][j] + other.data[i][j];
    }
  }
  return res;
}

// Subtraction
template <typename T>
auto MatrixT<T>::operator-(const MatrixT<T>& other) const -> MatrixT<T> {
  if (rows != other.rows || cols != other.cols) {
    throw std::invalid_argument("Size mismatch for subtraction.");
  }

  MatrixT<T> res(rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      res.data[i][j] = data[i][j] - other.data[i][j];
    }
  }
  return res;
}

// Scalar Multiplication
template <typename T>
auto MatrixT<T>::operator*(T scalar) const -> MatrixT<T> {
  MatrixT<T> res(rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      res.data[i][j] = data[i][j] * scalar;
    }
  }
  return res;
}

// Matrix Multiplication
template <typename T>
auto MatrixT<T>::operator*(const MatrixT<T>& other) const -> MatrixT<T> {
  if (cols != other.rows) {
    throw std::invalid_argument("Incompatible dimensions for multiplication.");
  }

  MatrixT<T> res(rows, other.cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < other.cols; ++j) {
      for (int k = 0; k < cols; ++k) {
        res.data[i][j] += data[i][k] * other.data[k][j];
      }
    }
  }
  return res;
}

// Display
template <typename T>
void MatrixT<T>::display() const {
  for (const auto& row : data) {
    for (T val : row) {
      std::cout << val << "\t";
    }
    std::cout << "\n";
  }
}

#endif  // MATRIX_TPP