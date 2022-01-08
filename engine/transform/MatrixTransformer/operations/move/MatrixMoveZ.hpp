#pragma once

#include "transform/MatrixTransformer/operations/IMatrixOperation.hpp"

class MatrixMoveZ : public IMatrixOperation {
public:
    explicit MatrixMoveZ(float dz);
    Matrix<float, 4 ,4> GetMatrix() override;
    ~MatrixMoveZ() override = default;

private:
    float z;
};
