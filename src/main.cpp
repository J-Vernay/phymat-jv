#include <iostream>

#include "Matrix.hpp"


int main() {
    auto a = Mat22{1,2,  3,4};

    std::cout << a * 4 << " " << Matrix<1,2>{3,5} << '\n';

    for (auto& line : Matrix<3,2>{1,3,  3,5,  0,0}) {
        for (auto& value : line) {
            std::cout << value << " ";
        }
        std::cout << "\n";
    }
    return 0;
}

