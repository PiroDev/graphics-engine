#include "MatrixRotateZ.hpp"

#include <cmath>

MatrixRotateZ::MatrixRotateZ(float angle) : sinA(std::sin(angle)), cosA(std::cos(angle)) {}

Matrix<float, 4, 4> MatrixRotateZ::GetMatrix() {
    return Matrix<float, 4, 4>
            ({
                     {cosA, -sinA, 0, 0},
                     {sinA, cosA,  0, 0},
                     {0,    0,     1, 0},
                     {0,    0,     0, 1}
             });
}