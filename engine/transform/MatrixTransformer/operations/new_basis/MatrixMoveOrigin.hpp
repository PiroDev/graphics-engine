#pragma once

#include "transform/MatrixTransformer/operations/IMatrixOperation.hpp"
#include "core/primitives/Point3f/Point3f.hpp"

class MatrixMoveOrigin : public IMatrixOperation {
public:
    explicit MatrixMoveOrigin(Point3f p);
    Matrix<float, 4 ,4> GetMatrix() override;
    ~MatrixMoveOrigin() override = default;

private:
    Point3f p;
};
