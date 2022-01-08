#pragma once

#include "transform/MatrixTransformer/operations/IMatrixOperation.hpp"

class MatrixRotateEuler : public IMatrixOperation {
public:
    MatrixRotateEuler(float yaw, float pitch, float roll);
    Matrix<float, 4 ,4> GetMatrix() override;
    ~MatrixRotateEuler() override = default;

private:
    float yaw, pitch, roll;
};
