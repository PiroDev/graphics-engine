#include "MatrixScaleX.hpp"

MatrixScaleX::MatrixScaleX(float kx) : x(kx) {}

Matrix<float, 4, 4> MatrixScaleX::GetMatrix() {
    return Matrix<float, 4, 4>
            ({
                     {x, 0, 0, 0},
                     {0, 1, 0, 0},
                     {0, 0, 1, 0},
                     {0, 0, 0, 1}
             });
}
