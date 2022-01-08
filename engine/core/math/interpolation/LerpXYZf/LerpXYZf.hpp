#pragma once

#include "core/math/interpolation/Lerp/Lerp.hpp"

struct LerpXYZf {
    template <typename T>
    T operator()(T a, T b, float t) {
        Lerp lerp;
        float x = lerp(a.X(), b.X(), t);
        float y = lerp(a.Y(), b.Y(), t);
        float z = lerp(a.Z(), b.Z(), t);

        return {x,y,z};
    }
};
