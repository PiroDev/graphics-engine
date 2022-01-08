#include "MatrixRotateY.hpp"

#include <cmath>

MatrixRotateY::MatrixRotateY(float angle) : sinA(std::sin(angle)), cosA(std::cos(angle)) {}

Matrix<float, 4, 4> MatrixRotateY::GetMatrix() {
    return Matrix<float, 4, 4>
            ({
                     {cosA,  0, sinA, 0},
                     {0,     1, 0,    0},
                     {-sinA, 0, cosA, 0},
                     {0,     0, 0,    1}
             });
}