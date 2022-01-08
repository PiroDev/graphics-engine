#include "MatrixMoveZ.hpp"

MatrixMoveZ::MatrixMoveZ(float dz) : z(dz) {}

Matrix<float, 4, 4> MatrixMoveZ::GetMatrix() {
    return Matrix<float, 4, 4>
            ({
                     {1, 0, 0, 0},
                     {0, 1, 0, 0},
                     {0, 0, 1, 0},
                     {0, 0, z, 1}
             });
}
