#include "MatrixScaleZ.hpp"

MatrixScaleZ::MatrixScaleZ(float kz) : z(kz) {}

Matrix<float, 4, 4> MatrixScaleZ::GetMatrix() {
    return Matrix<float, 4, 4>
            ({
                     {1, 0, 0, 0},
                     {0, 1, 0, 0},
                     {0, 0, z, 0},
                     {0, 0, 0, 1}
             });
}