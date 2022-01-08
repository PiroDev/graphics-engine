#include "Point3f.hpp"

Point3f::Point3f() : x(0), y(0), z(0) {}

Point3f::Point3f(float x, float y, float z) : x(x), y(y), z(z) {}

float &Point3f::X() { return x; }

float &Point3f::Y() { return y; }

float &Point3f::Z() { return z; }

float Point3f::X() const { return x; }

float Point3f::Y() const { return y; }

float Point3f::Z() const { return z; }
