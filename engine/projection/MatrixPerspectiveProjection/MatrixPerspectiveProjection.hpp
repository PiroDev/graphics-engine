#pragma once

#include "transform/MatrixTransformer/operations/IMatrixOperation.hpp"

class MatrixPerspectiveProjection : public IMatrixOperation {
public:
    explicit MatrixPerspectiveProjection(float near, float z);
    ~MatrixPerspectiveProjection() override = default;
    Matrix<float, 4 ,4> GetMatrix() override;

private:
    float near;
    float z;
};
