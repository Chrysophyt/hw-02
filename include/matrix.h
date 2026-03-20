#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>

class Matrix {
private:
    int rows, cols;
    std::vector<std::vector<double>> data;
    static std::string clean(std::string s);

public:
    // Constructor
    Matrix(int r, int c);

    // Accessors
    void set(int r, int c, double val);
    double get(int r, int c) const;
    int getRows() const { return rows; }
    int getCols() const { return cols; }

    // For File I/O
    void writeToFile(const std::string& filename) const;
    static Matrix readFromFile(const std::string& filename);

    // For Math Operations
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    Matrix operator*(const Matrix& other) const;

    // For Display
    void display() const;
};

#endif
