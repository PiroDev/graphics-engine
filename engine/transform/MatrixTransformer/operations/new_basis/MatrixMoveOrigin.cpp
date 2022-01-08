#include "MatrixMoveOrigin.hpp"

MatrixMoveOrigin::MatrixMoveOrigin(Point3f p) : p(p) {}

Matrix<float, 4, 4> MatrixMoveOrigin::GetMatrix() {
    return Matrix<float, 4, 4>
            ({
                     {1,      0,      0,      0},
                     {0,      1,      0,      0},
                     {0,      0,      1,      0},
                     {-p.X(), -p.Y(), -p.Z(), 1}
             });
}
