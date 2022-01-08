#include "MatrixPerspectiveProjection.hpp"

MatrixPerspectiveProjection::MatrixPerspectiveProjection(float near, float z) : near(near), z(z) {}

Matrix<float, 4, 4> MatrixPerspectiveProjection::GetMatrix() {
    auto absZ = std::abs(z);
    if (absZ < 1e-16) {
        return Matrix<float, 4, 4>({
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
        });
    }

    return Matrix<float, 4, 4>({
            {near / absZ, 0,           0, 0},
            {0,           near / absZ, 0, 0},
            {0,           0,           1, 0},
            {0,           0,           0, 1}
    });
}
