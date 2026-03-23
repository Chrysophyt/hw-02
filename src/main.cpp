#include "matrix.h"
#include <iostream>

int main() {
    std::cout << "--- Matrix Application ---\n";
    
    Matrix A(2, 2);
    A.set(0, 0, 1); A.set(0, 1, 2);
    A.set(1, 0, 3); A.set(1, 1, 4);

    std::cout << "Matrix A:\n";
    A.display();

    Matrix B = A * 10.0;
    std::cout << "\nMatrix A * 10:\n";
    B.display();

    std::cout << "\nSaving Matrix B to file...\n";
    B.writeToFile("output.txt");
    std::cout << "Done!\n";

    return 0;
}
