#pragma once

#include <array> // std::array (fixed size array with utility methods)
#include <span>  // std::span (view to array (pointer+size), with utility methods)

#include <algorithm> // std::copy
#include <ranges>    // std::ranges::xxxx
#include <iterator>  // std::ostream_iterator
#include <iostream>  // std::ostream

// Matrix inherits from array<array<float, Column>, Row> for simplicity:
// It allows the following syntaxes:
//     Matrix<2,2> m = {1,2,3,4}; float v = m[0][1];  
//     for (auto& line : m) cout << line[0] << line[1] << endl;
template<int Rows, int Columns>
class Matrix : public std::array<std::array<float, Columns>, Rows> {    
public:
    // Accessors for rows and columns
    int rows() const { return Rows; }
    int columns() const { return Columns; }

    // Accessor for a single value.
    float value(int i, int j) const { return (*this)[i][j]; }
    float& value(int i, int j) { return (*this)[i][j]; }

    // Accessors for all values.
    std::span<float, Rows*Columns> values() {
        return std::span<float, Rows*Columns>{&(*this)[0][0], Rows*Columns};
    }
    std::span<float const, Rows*Columns> values() const {
        return std::span<float const, Rows*Columns>{&(*this)[0][0], Rows*Columns};
    }



    //===== Operator overloading =====
    
    bool operator==(Matrix const& other) const {
        return std::ranges::equal(values(), other.values());
    }
    
    Matrix& operator*=(float scalar) {
        for (float& value : values())
            value *= scalar;
        return *this;
    }
    friend Matrix operator*(Matrix m, float scalar) {
        return m *= scalar;
    }
    friend Matrix operator*(float scalar, Matrix m) {
        return m *= scalar;
    }

    // "cout << Matrix<2,2>{1,2,3,4}" will output "Matrix<2,2>{1,2,3,4,}"
    friend std::ostream& operator<<(std::ostream& os, Matrix const& m) {
        os << "Matrix<" << Rows << "," << Columns << ">{";
        std::ranges::copy(m.values(), std::ostream_iterator<float>(os, ","));
        return os << "}";
    }

};

// Short names for usual matrices.
using Mat22 = Matrix<2,2>;
using Mat33 = Matrix<3,3>;
using Mat44 = Matrix<4,4>;
