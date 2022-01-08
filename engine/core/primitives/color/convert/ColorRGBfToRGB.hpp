#pragma once

#include "core/primitives/color/ColorRGBf.hpp"
#include "core/primitives/color/ColorRGB.hpp"

struct ColorRGBfToRGB {
    ColorRGB operator() (const ColorRGBf &src) const;
};
