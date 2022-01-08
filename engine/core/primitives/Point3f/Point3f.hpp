#pragma once

class Point3f {
public:
    Point3f();
    Point3f(float x, float y, float z);
    float &X();
    float &Y();
    float &Z();
    [[nodiscard]] float X() const;
    [[nodiscard]] float Y() const;
    [[nodiscard]] float Z() const;

private:
    float x, y, z;
};
