#include "MatrixViewportToCanvas.hpp"

#include <cmath>
#include <iostream>

MatrixViewportToCanvas::MatrixViewportToCanvas(float fovX, float viewportWidth, float viewportHeight, float canvasWidth,
                                               float canvasHeight) {
    float aspectRatio = canvasWidth / canvasHeight;
    const float fovY = 2 * std::atan(std::tan(fovX / 2) / aspectRatio);
    xScale = canvasWidth / viewportWidth / (2 * std::tan(fovX / 2));
    yScale = canvasHeight / viewportHeight / (2 * std::tan(fovY / 2));

//    std::cout << h << " w " << w << std::endl;
}

Matrix<float, 4, 4> MatrixViewportToCanvas::GetMatrix() {
    return Matrix<float, 4, 4>
            ({
                     {xScale, 0,      0, 0},
                     {0,      yScale, 0, 0},
                     {0,      0,      1, 0},
                     {0,      0,      0, 1}
             });
}
