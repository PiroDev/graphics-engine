#include "MatrixCanvasToScreen.hpp"

MatrixCanvasToScreen::MatrixCanvasToScreen(float screenWidth, float screenHeight) : w(screenWidth),
                                                                                    h(screenHeight) {}

Matrix<float, 4, 4> MatrixCanvasToScreen::GetMatrix() {
    return Matrix<float, 4, 4>
            ({
                     {1,     0,     0, 0},
                     {0,     -1,    0, 0},
                     {0,     0,     1, 0},
                     {w / 2, h / 2, 0, 1},
             });
}
