#pragma once

#include <memory>
#include <vector>

#include "ProjectedFragment/ProjectedFragment.hpp"
#include "ColorBuffer/ColorBuffer.hpp"
#include "DepthBuffer/DepthBuffer.hpp"

struct DepthTest {
    void operator() (ColorBuffer &colorBuffer, DepthBuffer &depthBuffer,
                     const std::vector<ProjectedFragment> &fragments);
};
