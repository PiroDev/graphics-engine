#pragma once

#include "core/primitives/color/ColorRGBf.hpp"
#include "lighting/PointLight/PointLight.hpp"
#include "lighting/PhongFragment/PhongFragment.hpp"

class PhongShader {
public:
    ColorRGBf operator()(const std::shared_ptr<PointLight> &light,
                         const PhongFragment &fragment,
                         const Normal &viewN);
};
