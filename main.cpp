#include <iostream>
#include <vector>
#include <cassert>

#include "determinantMximizer.h"

int main() {
    unsigned int size = 0;
    std::cin >> size;

    std::vector<std::vector<double>> matrix(size, std::vector(size, 0.));

    for (auto& line: matrix) {
        for (auto& elem: line) {
            std::cin >> elem;
        }
    }

    DeterminantMaximizer determinantMaximizer(matrix);
    std:: cout << determinantMaximizer.Determinant() << '\n';

//    DeterminantMaximizer::FlipSideDiag(matrix, {0, 0}, {4, 4});

//    for (auto& line: matrix) {
//        for (auto& el: line) {
//            std::cout << el << ' ';
//        }
//        std::cout << '\n';
//    }

    return 0;
}
