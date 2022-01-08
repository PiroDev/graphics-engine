#include "MatrixScaleY.hpp"

MatrixScaleY::MatrixScaleY(float ky) : y(ky) {}

Matrix<float, 4, 4> MatrixScaleY::GetMatrix() {
    return Matrix<float, 4, 4>
            ({
                     {1, 0, 0, 0},
                     {0, y, 0, 0},
                     {0, 0, 1, 0},
                     {0, 0, 0, 1}
             });
}