#include "MatrixRotateEuler.hpp"

#include "MatrixRotateX.hpp"
#include "MatrixRotateY.hpp"

#include <memory>

MatrixRotateEuler::MatrixRotateEuler(float yaw, float pitch, float roll) : yaw(yaw), pitch(pitch), roll(roll) {}

Matrix<float, 4, 4> MatrixRotateEuler::GetMatrix() {
    auto rollMatrix = std::make_shared<MatrixRotateY>(roll)->GetMatrix();
    auto pitchMatrix = std::make_shared<MatrixRotateX>(pitch)->GetMatrix();
    auto yawMatrix = std::make_shared<MatrixRotateY>(yaw)->GetMatrix();

    auto result = rollMatrix * pitchMatrix * yawMatrix;

    return result;
}

