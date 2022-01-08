#include "MatrixViewTransform.hpp"

MatrixViewTransform::MatrixViewTransform(const std::shared_ptr<Camera> &camera) {
    eye = camera->EyePosition();
    auto lookAt = camera->LookAtPosition();
    auto upVector = camera->UpNormal();

    forwardAxis = Normal(lookAt, eye);
    leftAxis = upVector & forwardAxis;
    upAxis = forwardAxis & leftAxis;
}

Matrix<float, 4, 4> MatrixViewTransform::GetMatrix() {
    Matrix<float, 4, 4> moveMatrix
            ({
                     {1,        0,        0,        0},
                     {0,        1,        0,        0},
                     {0,        0,        1,        0},
                     {-eye.X(), -eye.Y(), -eye.Z(), 1}
             });

    Matrix<float, 4, 4> rotationMatrix
            ({
                     {leftAxis.X(), upAxis.X(), forwardAxis.X(), 0},
                     {leftAxis.Y(), upAxis.Y(), forwardAxis.Y(), 0},
                     {leftAxis.Z(), upAxis.Z(), forwardAxis.Z(), 0},
                     {0,            0,          0,               1}
             });

    return rotationMatrix * moveMatrix;
}
