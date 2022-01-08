#pragma once

#include <cstddef>
#include "core/primitives/color/ColorRGB.hpp"

class ProjectedFragment {
public:
    ProjectedFragment(unsigned x, unsigned y, float depth, ColorRGB color);

    [[nodiscard]] const unsigned &X() const;
    [[nodiscard]] const unsigned &Y() const;
    [[nodiscard]] const float &Depth() const;
    [[nodiscard]] const ColorRGB &Color() const;

    ~ProjectedFragment();

private:
    unsigned x, y;
    float depth;
    ColorRGB color;
};






