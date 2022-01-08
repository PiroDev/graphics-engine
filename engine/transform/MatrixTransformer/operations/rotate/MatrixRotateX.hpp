#pragma once

#include "transform/MatrixTransformer/operations/IMatrixOperation.hpp"

class MatrixRotateX : public IMatrixOperation {
public:
    explicit MatrixRotateX(float angle);
    Matrix<float, 4 ,4> GetMatrix() override;
    ~MatrixRotateX() override = default;

private:
    float sinA;
    float cosA;
};
