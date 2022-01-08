#pragma once

#include "core/primitives/color/ColorRGBf.hpp"

class PhongModel {
public:
    PhongModel(ColorRGBf ambient, ColorRGBf diffuse, ColorRGBf specular);

    ColorRGBf &Ambient();
    [[nodiscard]] const ColorRGBf &Ambient() const;

    ColorRGBf &Diffuse();
    [[nodiscard]] const ColorRGBf &Diffuse() const;

    ColorRGBf &Specular();
    [[nodiscard]] const ColorRGBf &Specular() const;

private:
    ColorRGBf ambient;
    ColorRGBf diffuse;
    ColorRGBf specular;
};
