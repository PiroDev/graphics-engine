#pragma once

#include "core/primitives/Point3f/Point3f.hpp"
#include "visibility/DepthTest/ColorBuffer/ColorBuffer.hpp"

struct DrawLine {
    void operator() (ColorBuffer &colorBuffer, const Point3f &start, const Point3f &end, const ColorRGB &color = ColorRGB(255, 0, 0));
};
