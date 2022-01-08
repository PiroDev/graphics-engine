#pragma once

#include "transform/MatrixTransformer/operations/IMatrixOperation.hpp"

class MatrixRotateZ : public IMatrixOperation {
public:
    MatrixRotateZ(float angle);
    Matrix<float, 4 ,4> GetMatrix() override;
    ~MatrixRotateZ() = default;

private:
    float sinA;
    float cosA;
};
