#include "MatrixMoveX.hpp"

#include <glm/gtc/matrix_transform.hpp>

MatrixMoveX::MatrixMoveX(float dx) : x(dx) {}

Matrix<float, 4, 4> MatrixMoveX::GetMatrix() {
    return Matrix<float, 4, 4>
            ({
                     {1, 0, 0, 0},
                     {0, 1, 0, 0},
                     {0, 0, 1, 0},
                     {x, 0, 0, 1}
             });
}
