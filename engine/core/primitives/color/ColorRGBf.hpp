#pragma once

#include <ostream>

class ColorRGBf {
public:
    ColorRGBf();
    ColorRGBf(float r, float g, float b);

    [[nodiscard]] float R() const;
    float &R();
    [[nodiscard]] float G() const;
    float &G();
    [[nodiscard]] float B() const;
    float &B();

    ColorRGBf operator* (const ColorRGBf &right) const;
    ColorRGBf &operator*= (const ColorRGBf &right);

    ColorRGBf operator+ (const ColorRGBf &right) const;
    ColorRGBf &operator+= (const ColorRGBf &right);

    ColorRGBf operator* (float intensity) const;
    ColorRGBf &operator*= (float intensity);

    ~ColorRGBf() = default;

private:
    void applyIntensity(float intensity);
    float r, g, b;
};

ColorRGBf operator* (float intensity, const ColorRGBf &color);
