#include "ProjectedFragment.hpp"

ProjectedFragment::ProjectedFragment(unsigned x, unsigned y, float depth, ColorRGB color) : x(x), y(y), depth(depth),
                                                                                        color(color) {}

const unsigned &ProjectedFragment::X() const {
    return x;
}

const unsigned &ProjectedFragment::Y() const {
    return y;
}

const float &ProjectedFragment::Depth() const {
    return depth;
}

const ColorRGB &ProjectedFragment::Color() const {
    return color;
}

ProjectedFragment::~ProjectedFragment() = default;
