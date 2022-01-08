#pragma once

#include "transform/MatrixTransformer/operations/IMatrixOperation.hpp"

class MatrixRotateY : public IMatrixOperation {
public:
    MatrixRotateY(float angle);
    Matrix<float, 4 ,4> GetMatrix() override;
    ~MatrixRotateY() = default;

private:
    float sinA;
    float cosA;
};
