[![Tests](https://github.com/Chrysophyt/hw-02/actions/workflows/ci.yml/badge.svg)](https://github.com/Chrysophyt/hw-02/actions/workflows/ci.yml)
[![codecov](https://codecov.io/gh/Chrysophyt/hw-02/graph/badge.svg?token=JQH884LD64)](https://codecov.io/gh/Chrysophyt/hw-02)

## Overview

A C++ template-based matrix computation library with the following features:

- **Generic**: Works with any arithmetic type (int, float, double, etc.)
- **Operations**: Matrix addition, subtraction, scalar multiplication, matrix multiplication
- **File I/O**: Read/write matrices to/from files
- **Display**: Print matrices to console

## Build

```bash
mkdir build
cd build
cmake ..
make
```

## Run the Application

```bash
./matrix_app
```

## Run Tests

```bash
./matrix_test
```

## Example Usage

```cpp
#include "matrix.h"

int main() {
  // Create a 2x2 matrix (defaults double)
  Matrix A(2, 2);
  A.set(0, 0, 1);
  A.set(0, 1, 2);
  A.set(1, 0, 3);
  A.set(1, 1, 4);

  // Matrix addition
  Matrix B = A + A;

  // Matrix subtraction
  Matrix C = A - B;

  // Scalar multiplication
  Matrix D = A * 2.5;

  // Matrix multiplication
  Matrix E = A * B;

  // Display
  A.display();

  // File I/O
  A.writeToFile("matrix.txt");
  Matrix F = Matrix::readFromFile("matrix.txt");
}
```

## Testing and Code Coverage
This project uses Google Test (gTest) for unit testing and gcovr to generate HTML code coverage reports.

**Prerequisites**
Before building and running the tests, ensure you have the following installed on your system:
- A C++ compiler (GCC or Clang)
- CMake (version 3.14 or higher)
- gcovr (for generating the coverage reports)

### Build the Project
We use an out-of-source build to keep the generated files completely separate from the source code. Run the following commands from the root directory of the project:

```Bash
# Create the build directory and navigate into it
mkdir build
cd build

# Configure the project with CMake
cmake ..

# Compile the code and the test suite
make
```

### Run the Tests
Once compiled, you must execute the test binary to generate the .gcda execution data files required for the coverage report.

While still inside the build/ directory, run:

```Bash
./matrix_test
gcovr --root .. . --html --html-details --exclude-throw-branches -o coverage.html
```
You should see a green gTest output indicating that all tests have passed. If a test crashes or fails, fix the code before proceeding to the coverage step.
With the tests successfully executed, you can also use gcovr to parse the coverage data and generate a detailed HTML webpage.
