#include "ColorRGBf.hpp"

ColorRGBf::ColorRGBf() : r(0), g(0), b(0) {}
ColorRGBf::ColorRGBf(float r, float g, float b) : r(r), g(g), b(b) {}

ColorRGBf &ColorRGBf::operator*=(float intensity) {
    applyIntensity(intensity);
    return *this;
}

ColorRGBf ColorRGBf::operator*(float intensity) const {
    ColorRGBf newColor(*this);
    newColor.applyIntensity(intensity);
    return newColor;
}

void ColorRGBf::applyIntensity(float intensity) {
    r *= intensity;
    g *= intensity;
    b *= intensity;
}

float ColorRGBf::R() const {
    return r;
}

float &ColorRGBf::R() {
    return r;
}

float ColorRGBf::G() const {
    return g;
}

float &ColorRGBf::G() {
    return g;
}

float ColorRGBf::B() const {
    return b;
}

float &ColorRGBf::B() {
    return b;
}

ColorRGBf ColorRGBf::operator*(const ColorRGBf &right) const {
    return {r * right.r, g * right.g, b * right.b};
}

ColorRGBf &ColorRGBf::operator*=(const ColorRGBf &right) {
    r *= right.r;
    g *= right.g;
    b *= right.b;

    return *this;
}

ColorRGBf ColorRGBf::operator+(const ColorRGBf &right) const {
    return {r + right.r, g + right.g, b + right.b};
}

ColorRGBf &ColorRGBf::operator+=(const ColorRGBf &right) {
    r += right.r;
    g += right.g;
    b += right.b;

    return *this;
}

ColorRGBf operator* (float intensity, const ColorRGBf &color) {
    return color * intensity;
}
