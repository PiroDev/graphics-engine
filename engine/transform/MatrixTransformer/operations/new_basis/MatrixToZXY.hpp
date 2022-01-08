#pragma once

#include "transform/MatrixTransformer/operations/IMatrixOperation.hpp"

class MatrixToZXY : public IMatrixOperation {
public:
    MatrixToZXY() = default;
    Matrix<float, 4 ,4> GetMatrix() override;
    ~MatrixToZXY() override = default;
};
