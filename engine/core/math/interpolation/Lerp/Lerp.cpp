#include "Lerp.hpp"

float Lerp::operator()(float a, float b, float t) const {
    return (1 - t) * a + b * t;
}