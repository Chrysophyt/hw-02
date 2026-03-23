#include "matrix.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

// Constructor
Matrix::Matrix(int row, int col)
    : rows(row), cols(col), data(row, std::vector<double>(col, 0.0)) {}

// Accessors
void Matrix::set(int row, int col, double val) { data[row][col] = val; }
auto Matrix::get(int row, int col) const -> double { return data[row][col]; }

// Private string cleaner
auto Matrix::clean(std::string text) -> std::string {
  // Boost::algorithm dependencies needed for this
  // NOLINTBEGIN(boost-use-ranges)
  text.erase(std::remove(text.begin(), text.end(), '['), text.end());
  text.erase(std::remove(text.begin(), text.end(), ']'), text.end());
  text.erase(std::remove(text.begin(), text.end(), ','), text.end());
  // NOLINTEND(boost-use-ranges)
  return text;
}

// Write to File
void Matrix::writeToFile(const std::string& filename) const {
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
auto Matrix::readFromFile(const std::string& filename) -> Matrix {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file.");
  }

  std::vector<std::vector<double>> temp_data;
  std::string line;

  while (std::getline(file, line)) {
    if (line.find('[') != std::string::npos &&
        line.find_first_not_of(" []\n,") != std::string::npos) {
      std::vector<double> row;
      std::stringstream strings(clean(line));
      double val = 0.0;

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

  Matrix result(static_cast<int>(temp_data.size()),
                static_cast<int>(temp_data[0].size()));
  result.data = temp_data;
  return result;
}

// Addition
auto Matrix::operator+(const Matrix& other) const -> Matrix {
  if (rows != other.rows || cols != other.cols) {
    throw std::invalid_argument("Size mismatch for addition.");
  }

  Matrix res(rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      res.data[i][j] = data[i][j] + other.data[i][j];
    }
  }
  return res;
}

// Subtraction
auto Matrix::operator-(const Matrix& other) const -> Matrix {
  if (rows != other.rows || cols != other.cols) {
    throw std::invalid_argument("Size mismatch for subtraction.");
  }

  Matrix res(rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      res.data[i][j] = data[i][j] - other.data[i][j];
    }
  }
  return res;
}

// Scalar Multiplication
auto Matrix::operator*(double scalar) const -> Matrix {
  Matrix res(rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      res.data[i][j] = data[i][j] * scalar;
    }
  }
  return res;
}

// Matrix Multiplication
auto Matrix::operator*(const Matrix& other) const -> Matrix {
  if (cols != other.rows) {
    throw std::invalid_argument("Incompatible dimensions for multiplication.");
  }

  Matrix res(rows, other.cols);
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
void Matrix::display() const {
  for (const auto& row : data) {
    for (double val : row) {
      std::cout << val << "\t";
    }
    std::cout << "\n";
  }
}
