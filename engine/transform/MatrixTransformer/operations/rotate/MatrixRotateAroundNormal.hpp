#pragma once

#include "transform/MatrixTransformer/operations/IMatrixOperation.hpp"
#include "core/primitives/Normal/Normal.hpp"

class MatrixRotateAroundNormal : public IMatrixOperation {
public:
    MatrixRotateAroundNormal(Normal n, float angle);
    Matrix<float, 4 ,4> GetMatrix() override;
    ~MatrixRotateAroundNormal() override = default;

private:
    Normal n;
    float angle;
};
