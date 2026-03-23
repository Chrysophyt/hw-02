[![Tests](https://github.com/Chrysophyt/homework-02/actions/workflows/ci.yml/badge.svg)](https://github.com/Chrysophyt/homework-02/actions/workflows/ci.yml)
[![codecov](https://codecov.io/gh/Chrysophyt/homework-02/graph/badge.svg?token=JQH884LD64)](https://codecov.io/gh/Chrysophyt/homework-02)
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
