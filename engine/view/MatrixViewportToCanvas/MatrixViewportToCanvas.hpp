#pragma once

#include "transform/MatrixTransformer/operations/IMatrixOperation.hpp"

class MatrixViewportToCanvas : public IMatrixOperation {
public:
    MatrixViewportToCanvas(float fov, float viewportWidth, float viewportHeight, float canvasWidth, float canvasHeight);

    Matrix<float, 4, 4> GetMatrix() override;

private:
    float xScale;
    float yScale;
    float h;
    float w;
};
