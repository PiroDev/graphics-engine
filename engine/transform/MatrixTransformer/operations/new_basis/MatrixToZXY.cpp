#include "MatrixToZXY.hpp"

Matrix<float, 4, 4> MatrixToZXY::GetMatrix() {
    return Matrix<float, 4, 4>
            ({
                     {0, 0, 1, 0},
                     {1, 0, 0, 0},
                     {0, 1, 0, 0},
                     {0, 0, 0, 1}
             });
}
