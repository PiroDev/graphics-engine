#pragma once

#include "transform/MatrixTransformer/operations/IMatrixOperation.hpp"

class MatrixCanvasToScreen : public IMatrixOperation {
public:
    MatrixCanvasToScreen(float screenWidth, float screenHeight);
    Matrix<float, 4 ,4> GetMatrix() override;
    ~MatrixCanvasToScreen() override = default;

private:
    float w, h;
};
