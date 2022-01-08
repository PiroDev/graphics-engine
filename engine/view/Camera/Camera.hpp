#pragma once

#include <memory>

#include "core/primitives/Normal/Normal.hpp"
#include "core/primitives/Point3f/Point3f.hpp"

class Camera {
public:
    Camera(Normal up, Point3f eye, Point3f lookAt, float pitch = 0, float yaw = 0);

    [[nodiscard]] const Normal &UpNormal() const;
    Normal &UpNormal();

    [[nodiscard]] const Point3f &EyePosition() const;
    Point3f &EyePosition();

    [[nodiscard]] const Point3f &LookAtPosition() const;
    Point3f &LookAtPosition();

    [[nodiscard]] float PitchAngle() const;
    [[nodiscard]] float YawAngle() const;

    void Pitch(float angle);
    void Yaw(float angle);
    void Scale(float ratio);
    void MoveRightAxis(float delta);
    void MoveForwardAxis(float delta);

private:
    void pitch(float angle);
    void yaw(float angle);

private:
    Normal up;
    Point3f eye;
    Point3f lookAt;
    float pitchAngle;
    float yawAngle;
};
