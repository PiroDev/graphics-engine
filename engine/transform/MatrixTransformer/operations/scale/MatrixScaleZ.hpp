#pragma once

#include "transform/MatrixTransformer/operations/IMatrixOperation.hpp"

class MatrixScaleZ : public IMatrixOperation {
public:
    explicit MatrixScaleZ(float kz);
    Matrix<float, 4 ,4> GetMatrix() override;
    ~MatrixScaleZ() override = default;

private:
    float z;
};
