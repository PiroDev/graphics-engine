#pragma once

#include "core/primitives/Point3f/Point3f.hpp"

class Normal {
public:
    Normal();
    Normal(float x, float y, float z);
    Normal(const Point3f &start, const Point3f &end);

    float &X();
    [[nodiscard]] const float &X() const;
    float &Y();
    [[nodiscard]] const float &Y() const;
    float &Z();
    [[nodiscard]] const float &Z() const;

    float operator*(const Normal &n) const;
    Normal operator&(const Normal &n) const;
    Normal operator-() const;

private:
    void normalize();

    float x, y, z;
};
