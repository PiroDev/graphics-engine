#pragma once

#include "transform/MatrixTransformer/operations/IMatrixOperation.hpp"

class MatrixScaleY : public IMatrixOperation {
public:
    explicit MatrixScaleY(float ky);
    Matrix<float, 4 ,4> GetMatrix() override;
    ~MatrixScaleY() override = default;

private:
    float y;
};
