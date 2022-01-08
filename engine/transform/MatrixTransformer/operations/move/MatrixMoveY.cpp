#include "MatrixMoveY.hpp"

MatrixMoveY::MatrixMoveY(float dy) : y(dy) {}

Matrix<float, 4, 4> MatrixMoveY::GetMatrix() {
    return Matrix<float, 4, 4>
            ({
                     {1, 0, 0, 0},
                     {0, 1, 0, 0},
                     {0, 0, 1, 0},
                     {0, y, 0, 1}
             });
}
