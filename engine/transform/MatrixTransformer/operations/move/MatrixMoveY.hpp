#pragma once

#include "transform/MatrixTransformer/operations/IMatrixOperation.hpp"

class MatrixMoveY : public IMatrixOperation {
public:
    explicit MatrixMoveY(float dy);
    Matrix<float, 4 ,4> GetMatrix() override;
    ~MatrixMoveY() override = default;

private:
    float y;
};
