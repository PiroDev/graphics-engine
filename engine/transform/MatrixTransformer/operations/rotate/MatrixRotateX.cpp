#include "MatrixRotateX.hpp"

#include <cmath>

MatrixRotateX::MatrixRotateX(float angle) : sinA(std::sin(angle)), cosA(std::cos(angle)) {}

Matrix<float, 4, 4> MatrixRotateX::GetMatrix() {
    return Matrix<float, 4, 4>
            ({
                     {1, 0,     0,    0},
                     {0, cosA,  sinA, 0},
                     {0, -sinA, cosA, 0},
                     {0, 0,     0,    1}
             });
}
