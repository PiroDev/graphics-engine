#include "Normal.hpp"

#include <cmath>

Normal::Normal(float x, float y, float z) : x(x), y(y), z(z) {
    normalize();
}

Normal::Normal(const Point3f &start, const Point3f &end)
        : x(end.X() - start.X()), y(end.Y() - start.Y()), z(end.Z() - start.Z()) {
    normalize();
}

float &Normal::X() {
    return x;
}

float &Normal::Y() {
    return y;
}

float &Normal::Z() {
    return z;
}

const float &Normal::X() const {
    return x;
}

const float &Normal::Y() const {
    return y;
}

const float &Normal::Z() const {
    return z;
}

float Normal::operator*(const Normal &right) const {
    return x * right.x + y * right.y + z * right.z;
}

Normal Normal::operator&(const Normal &right) const {
    float xRes = y * right.z - z * right.y;
    float yRes = z * right.x - x * right.z;
    float zRes = x * right.y - y * right.x;

    return {xRes, yRes, zRes};
}

void Normal::normalize() {
    float length = std::sqrt(x * x + y * y + z * z);
    x /= length;
    y /= length;
    z /= length;
}

Normal Normal::operator-() const {
    return {-x, -y, -z};
}

Normal::Normal() : x(0), y(0), z(0) {}
