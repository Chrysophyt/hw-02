#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

// Constructor
Matrix::Matrix(int r, int c) : rows(r), cols(c), data(r, std::vector<double>(c, 0.0)) {}

// Accessors
void Matrix::set(int r, int c, double val) { data[r][c] = val; }
double Matrix::get(int r, int c) const { return data[r][c]; }

// Private string cleaner
std::string Matrix::clean(std::string s) {
    s.erase(std::remove(s.begin(), s.end(), '['), s.end());
    s.erase(std::remove(s.begin(), s.end(), ']'), s.end());
    s.erase(std::remove(s.begin(), s.end(), ','), s.end());
    return s;
}

// Write to File
void Matrix::writeToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Could not open file for writing.");

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
Matrix Matrix::readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Could not open file.");

    std::vector<std::vector<double>> temp_data;
    std::string line;
    
    while (std::getline(file, line)) {
        if (line.find('[') != std::string::npos && line.find_first_not_of(" []\n,") != std::string::npos) {
            std::vector<double> row;
            std::stringstream ss(clean(line));
            double val;
            while (ss >> val) row.push_back(val);
            if (!row.empty()) temp_data.push_back(row);
        }
    }

    if (temp_data.empty()) throw std::runtime_error("File is empty or invalid format.");

    Matrix m(temp_data.size(), temp_data[0].size());
    m.data = temp_data;
    return m;
}

// Addition
Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) throw std::invalid_argument("Size mismatch for addition.");
    Matrix res(rows, cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j) res.data[i][j] = data[i][j] + other.data[i][j];
    return res;
}

// Subtraction
Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) throw std::invalid_argument("Size mismatch for subtraction.");
    Matrix res(rows, cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j) res.data[i][j] = data[i][j] - other.data[i][j];
    return res;
}

// Scalar Multiplication
Matrix Matrix::operator*(double scalar) const {
    Matrix res(rows, cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j) res.data[i][j] = data[i][j] * scalar;
    return res;
}

// Matrix Multiplication
Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) throw std::invalid_argument("Incompatible dimensions for multiplication.");
    Matrix res(rows, other.cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < other.cols; ++j)
            for (int k = 0; k < cols; ++k)
                res.data[i][j] += data[i][k] * other.data[k][j];
    return res;
}

// Display
void Matrix::display() const {
    for (const auto& row : data) {
        for (double val : row) std::cout << val << "\t";
        std::cout << "\n";
    }
}