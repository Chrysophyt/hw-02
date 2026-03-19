#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <sstream>

class Matrix {
private:
    int rows, cols;
    std::vector<std::vector<double>> data;

    // Helper to clean formatting characters from strings
    static std::string clean(std::string s) {
        s.erase(std::remove(s.begin(), s.end(), '['), s.end());
        s.erase(std::remove(s.begin(), s.end(), ']'), s.end());
        s.erase(std::remove(s.begin(), s.end(), ','), s.end());
        return s;
    }

public:
    Matrix(int r, int c) : rows(r), cols(c), data(r, std::vector<double>(c, 0.0)) {}

    // Accessor for setting values manually in the example
    void set(int r, int c, double val) { data[r][c] = val; }

    // 1a. Write to File
    void writeToFile(const std::string& filename) {
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

    // 1b. Read from File
    static Matrix readFromFile(const std::string& filename) {
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

        Matrix m(temp_data.size(), temp_data[0].size());
        m.data = temp_data;
        return m;
    }

    // 2. Addition & Subtraction
    Matrix operator+(const Matrix& other) {
        if (rows != other.rows || cols != other.cols) throw std::invalid_argument("Size mismatch");
        Matrix res(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j) res.data[i][j] = data[i][j] + other.data[i][j];
        return res;
    }

    Matrix operator-(const Matrix& other) {
        if (rows != other.rows || cols != other.cols) throw std::invalid_argument("Size mismatch");
        Matrix res(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j) res.data[i][j] = data[i][j] - other.data[i][j];
        return res;
    }

    // 3. Scalar Multiplication
    Matrix operator*(double scalar) {
        Matrix res(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j) res.data[i][j] = data[i][j] * scalar;
        return res;
    }

    // 4. Matrix Multiplication
    Matrix operator*(const Matrix& other) {
        if (cols != other.rows) throw std::invalid_argument("Incompatible dimensions for multiplication");
        Matrix res(rows, other.cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < other.cols; ++j)
                for (int k = 0; k < cols; ++k)
                    res.data[i][j] += data[i][k] * other.data[k][j];
        return res;
    }

    void display() const {
        for (const auto& row : data) {
            for (double val : row) std::cout << val << " ";
            std::cout << "\n";
        }
    }
};

// --- EXAMPLE USAGE ---
int main() {
    // Create a 3x2 matrix
    Matrix A(3, 2);
    A.set(0,0, 1); A.set(0,1, 2);
    A.set(1,0, 3); A.set(1,1, 4);
    A.set(2,0, 5); A.set(2,1, 6);

    std::cout << "Matrix A:\n";
    A.display();

    // 1. Write to file
    A.writeToFile("matrix_a.txt");
    std::cout << "\nSaved A to matrix_a.txt\n";

    // 2. Read from file
    Matrix B = Matrix::readFromFile("matrix_a.txt");
    
    // 3. Scalar Multiplication
    Matrix C = B * 2.0;
    std::cout << "\nMatrix B (from file) * 2.0:\n";
    C.display();

    // 4. Matrix Multiplication
    // Let's multiply A (3x2) by a 2x2 matrix
    Matrix D(2, 2);
    D.set(0,0, 1); D.set(0,1, 0);
    D.set(1,0, 0); D.set(1,1, 1); // Identity matrix

    Matrix E = A * D;
    std::cout << "\nMatrix A * Identity Matrix:\n";
    E.display();

    return 0;
}