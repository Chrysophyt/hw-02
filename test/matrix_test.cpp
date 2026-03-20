#include <gtest/gtest.h>
#include "matrix.h"
#include <cstdio>

TEST(MatrixTest, InitializationAndAccess) {
    Matrix m(2, 3);
    
    // Check dimensions
    EXPECT_EQ(m.getRows(), 2);
    EXPECT_EQ(m.getCols(), 3);

    // Check setting and getting a value
    m.set(0, 1, 5.5);
    EXPECT_DOUBLE_EQ(m.get(0, 1), 5.5);
}

TEST(MatrixTest, MatrixAddition) {
    Matrix m1(2, 2);
    m1.set(0, 0, 1.0); m1.set(0, 1, 2.0);
    m1.set(1, 0, 3.0); m1.set(1, 1, 4.0);

    Matrix m2(2, 2);
    m2.set(0, 0, 5.0); m2.set(0, 1, 6.0);
    m2.set(1, 0, 7.0); m2.set(1, 1, 8.0);

    Matrix result = m1 + m2;

    // 1+5 = 6, 4+8 = 12
    EXPECT_DOUBLE_EQ(result.get(0, 0), 6.0);
    EXPECT_DOUBLE_EQ(result.get(0, 1), 8.0);
    EXPECT_DOUBLE_EQ(result.get(1, 0), 10.0);
    EXPECT_DOUBLE_EQ(result.get(1, 1), 12.0);
}

TEST(MatrixTest, MatrixSubtraction) {
    Matrix m1(2, 2);
    m1.set(0, 0, 5.0); m1.set(0, 1, 5.0);
    m1.set(1, 0, 5.0); m1.set(1, 1, 5.0);

    Matrix m2(2, 2);
    m2.set(0, 0, 2.0); m2.set(0, 1, 3.0);
    m2.set(1, 0, 6.0); m2.set(1, 1, -1.0);

    Matrix result = m1 - m2;

    // Expected:
    // [ (5-2), (5-3)  ] -> [  3.0, 2.0 ]
    // [ (5-6), (5--1) ] -> [ -1.0, 6.0 ]
    EXPECT_DOUBLE_EQ(result.get(0, 0), 3.0);
    EXPECT_DOUBLE_EQ(result.get(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(result.get(1, 0), -1.0);
    EXPECT_DOUBLE_EQ(result.get(1, 1), 6.0);
}

TEST(MatrixTest, MatrixMultiplication) {
    // 2 rows, 3 columns
    Matrix m1(2, 3);
    m1.set(0, 0, 1.0); m1.set(0, 1, 2.0); m1.set(0, 2, 3.0);
    m1.set(1, 0, 4.0); m1.set(1, 1, 5.0); m1.set(1, 2, 6.0);

    // 3 rows, 2 columns
    Matrix m2(3, 2);
    m2.set(0, 0, 7.0);  m2.set(0, 1, 8.0);
    m2.set(1, 0, 9.0);  m2.set(1, 1, 10.0);
    m2.set(2, 0, 11.0); m2.set(2, 1, 12.0);

    // Result should be 2x2
    Matrix result = m1 * m2;

    EXPECT_EQ(result.getRows(), 2);
    EXPECT_EQ(result.getCols(), 2);

    // Expected Calculations:
    // Row 0, Col 0: (1*7 + 2*9 + 3*11) = 58.0
    // Row 0, Col 1: (1*8 + 2*10 + 3*12) = 64.0
    // Row 1, Col 0: (4*7 + 5*9 + 6*11) = 139.0
    // Row 1, Col 1: (4*8 + 5*10 + 6*12) = 154.0
    EXPECT_DOUBLE_EQ(result.get(0, 0), 58.0);
    EXPECT_DOUBLE_EQ(result.get(0, 1), 64.0);
    EXPECT_DOUBLE_EQ(result.get(1, 0), 139.0);
    EXPECT_DOUBLE_EQ(result.get(1, 1), 154.0);
}

TEST(MatrixTest, ScalarMultiplication) {
    Matrix m(2, 2);
    m.set(0, 0, 2.0);
    m.set(1, 1, 3.0);

    Matrix result = m * 2.5;

    EXPECT_DOUBLE_EQ(result.get(0, 0), 5.0);
    EXPECT_DOUBLE_EQ(result.get(1, 1), 7.5);
}

// --- 3. File I/O Tests ---
TEST(MatrixTest, FileReadWrite) {
    Matrix m1(2, 2);
    m1.set(0, 0, 9.99);
    m1.set(1, 1, -4.5);

    std::string testFilename = "test_matrix_io.txt";

    // Write it to a file
    m1.writeToFile(testFilename);

    // Read it back into a new matrix
    Matrix m2 = Matrix::readFromFile(testFilename);

    // Verify the data survived the round trip
    EXPECT_EQ(m2.getRows(), 2);
    EXPECT_EQ(m2.getCols(), 2);
    EXPECT_DOUBLE_EQ(m2.get(0, 0), 9.99);
    EXPECT_DOUBLE_EQ(m2.get(1, 1), -4.5);

    // Clean up the temporary test file so we don't clutter the directory
    std::remove(testFilename.c_str());
}

TEST(MatrixTest, DisplayOutput) {
    Matrix m(2, 2);
    m.set(0, 0, 1.5); m.set(0, 1, 2.5);
    m.set(1, 0, 3.5); m.set(1, 1, 4.5);

    // 1. Tell gTest to start recording terminal output
    testing::internal::CaptureStdout();

    // 2. Call your function (it will print to the hidden recorder instead of the screen)
    m.display();

    // 3. Stop recording and grab the output as a string
    std::string output = testing::internal::GetCapturedStdout();

    // 4. Verify the string matches exactly what we expect based on your implementation
    std::string expected_output = "1.5\t2.5\t\n3.5\t4.5\t\n";
    
    EXPECT_EQ(output, expected_output);
}
