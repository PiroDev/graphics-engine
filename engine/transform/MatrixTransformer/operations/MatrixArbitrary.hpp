#pragma once

#include "transform/MatrixTransformer/operations/IMatrixOperation.hpp"

class MatrixArbitrary : public IMatrixOperation {
public:
    explicit MatrixArbitrary(Matrix<float, 4, 4> matrix);
    Matrix<float, 4 ,4> GetMatrix() override;
    ~MatrixArbitrary() override = default;

private:
    Matrix<float, 4, 4> matrix;
};
