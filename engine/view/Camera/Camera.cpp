#include <transform/MatrixTransformer/operations/rotate/MatrixRotateAroundNormal.hpp>
#include <transform/MatrixTransformer/MatrixTransformer.hpp>
#include <transform/MatrixTransformer/operations/new_basis/MatrixMoveOrigin.hpp>
#include <transform/MatrixTransformer/operations/rotate/MatrixRotateY.hpp>
#include <transform/MatrixTransformer/operations/scale/MatrixScaleXYZ.hpp>
#include "Camera.hpp"

Camera::Camera(Normal up, Point3f eye, Point3f lookAt, float pitchAngle, float yawAngle)
    : up(up), eye(eye), lookAt(lookAt), pitchAngle(pitchAngle), yawAngle(yawAngle) {
}

const Normal &Camera::UpNormal() const {
    return up;
}

Normal &Camera::UpNormal() {
    return up;
}

const Point3f &Camera::EyePosition() const {
    return eye;
}

Point3f &Camera::EyePosition() {
    return eye;
}

const Point3f &Camera::LookAtPosition() const {
    return lookAt;
}

Point3f &Camera::LookAtPosition() {
    return lookAt;
}

void Camera::Pitch(float angle) {
    pitch(angle);
}

void Camera::Yaw(float angle) {
    yaw(angle);
}

void Camera::pitch(float angle) {
    if (pitchAngle + angle >= 89.f * M_PI / 180.f || pitchAngle + angle <= -89.f * M_PI / 180.f) {
        return;
    }

    pitchAngle += angle;

    auto viewN = Normal(eye, lookAt);
    auto rightN = viewN & up;

    auto rotate = std::make_shared<MatrixRotateAroundNormal>(rightN, angle);

    MatrixTransformer transformer;

    auto moveToOrigin = std::make_shared<MatrixMoveOrigin>(lookAt);
    auto moveBack = std::make_shared<MatrixMoveOrigin>(Point3f(-lookAt.X(), -lookAt.Y(), -lookAt.Z()));
    transformer.AddOperation(moveToOrigin);
    transformer.AddOperation(rotate);
    transformer.AddOperation(moveBack);

    transformer.ApplyTransforms(eye);
}

void Camera::yaw(float angle) {
    yawAngle += angle;

    auto rotate = std::make_shared<MatrixRotateY>(angle);

    MatrixTransformer transformer;

    auto moveToOrigin = std::make_shared<MatrixMoveOrigin>(lookAt);
    auto moveBack = std::make_shared<MatrixMoveOrigin>(Point3f(-lookAt.X(), -lookAt.Y(), -lookAt.Z()));
    transformer.AddOperation(moveToOrigin);
    transformer.AddOperation(rotate);
    transformer.AddOperation(moveBack);

    transformer.ApplyTransforms(eye);
}

void Camera::Scale(float ratio) {
    auto scale = std::make_shared<MatrixScaleXYZ>(ratio, ratio, ratio);

    MatrixTransformer transformer;

    auto moveToOrigin = std::make_shared<MatrixMoveOrigin>(lookAt);
    auto moveBack = std::make_shared<MatrixMoveOrigin>(Point3f(-lookAt.X(), -lookAt.Y(), -lookAt.Z()));
    transformer.AddOperation(moveToOrigin);
    transformer.AddOperation(scale);
    transformer.AddOperation(moveBack);

    transformer.ApplyTransforms(eye);
}

void Camera::MoveRightAxis(float delta) {
    auto viewN = Normal(eye, lookAt);

    auto rightN = viewN & up;
    auto rightV = delta * MathVector<float, 3>({rightN.X(), rightN.Y(), rightN.Z()});

    eye.X() += rightV[0];
    eye.Y() += rightV[1];
    eye.Z() += rightV[2];

    lookAt.X() += rightV[0];
    lookAt.Y() += rightV[1];
    lookAt.Z() += rightV[2];
}

void Camera::MoveForwardAxis(float delta) {
    auto viewN = Normal(eye, lookAt);

    auto rightN = viewN & up;
    auto forwardN = up & rightN;
    auto forwardV = delta * MathVector<float, 3>({forwardN.X(), forwardN.Y(), forwardN.Z()});

    eye.X() += forwardV[0];
    eye.Y() += forwardV[1];
    eye.Z() += forwardV[2];

    lookAt.X() += forwardV[0];
    lookAt.Y() += forwardV[1];
    lookAt.Z() += forwardV[2];
}

float Camera::PitchAngle() const {
    return pitchAngle;
}

float Camera::YawAngle() const {
    return yawAngle;
}
