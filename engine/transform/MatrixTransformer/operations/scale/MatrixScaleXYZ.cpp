#include "MatrixScaleXYZ.hpp"

MatrixScaleXYZ::MatrixScaleXYZ(float kx, float ky, float kz) : kx(kx), ky(ky), kz(kz) {}

Matrix<float, 4, 4> MatrixScaleXYZ::GetMatrix() {
    return Matrix<float, 4 ,4>({
            {kx, 0, 0, 0},
            {0, ky, 0, 0},
            {0, 0, kz, 0},
            {0, 0, 0, 1}
    });
}
