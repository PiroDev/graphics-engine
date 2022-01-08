#pragma once

#include "transform/MatrixTransformer/operations/IMatrixOperation.hpp"

class MatrixScaleXYZ : public IMatrixOperation {
public:
    explicit MatrixScaleXYZ(float kx, float ky, float kz);
    Matrix<float, 4 ,4> GetMatrix() override;
    ~MatrixScaleXYZ() override = default;

private:
    float kx, ky, kz;
};
