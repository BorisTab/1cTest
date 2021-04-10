#include <iostream>
#include <vector>

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
    std:: cout << determinantMaximizer.findMaxDet() << '\n';

    return 0;
}
