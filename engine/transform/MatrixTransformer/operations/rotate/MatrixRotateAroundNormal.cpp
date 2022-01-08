#include "MatrixRotateAroundNormal.hpp"

MatrixRotateAroundNormal::MatrixRotateAroundNormal(Normal n, float angle) : n(n), angle(angle) {}

Matrix<float, 4, 4> MatrixRotateAroundNormal::GetMatrix() {

    Matrix<float, 4, 4> iMatrix(glm::mat4(1));

    auto sinA = std::sin(angle);
    auto ratio = 2 * std::sin(angle / 2) * std::sin(angle / 2);

    Matrix<float, 4, 4> wMatrix
            ({
                     {0,      -n.Z(),  n.Y(), 0},
                     {n.Z(), 0,      -n.X(),  0},
                     {-n.Y(),  n.X(), 0,      0},
                     {0,      0,      0,      1},
             });

    Matrix<float, 4, 4> result = iMatrix + sinA * wMatrix + ratio * (wMatrix * wMatrix);

    return result;
}
