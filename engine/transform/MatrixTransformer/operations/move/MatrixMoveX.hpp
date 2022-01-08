#pragma once

#include "transform/MatrixTransformer/operations/IMatrixOperation.hpp"

class MatrixMoveX : public IMatrixOperation {
public:
    explicit MatrixMoveX(float dx);
    Matrix<float, 4 ,4> GetMatrix() override;
    ~MatrixMoveX() override = default;

private:
    float x;
};
