#pragma once

#include "transform/MatrixTransformer/operations/IMatrixOperation.hpp"

class MatrixScaleX : public IMatrixOperation {
public:
    explicit MatrixScaleX(float kx);
    Matrix<float, 4 ,4> GetMatrix() override;
    ~MatrixScaleX() override = default;

private:
    float x;
};
