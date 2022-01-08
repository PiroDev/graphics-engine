#pragma once

#include "core/math/interpolation/LerpXYZf/LerpXYZf.hpp"
#include "core/primitives/Point3f/Point3f.hpp"
#include "core/primitives/Normal/Normal.hpp"

#include <vector>

struct Fragment {
    Point3f p;
    Normal n;
};

struct FragmentsCmpByY {
    bool operator()(const Fragment &f1, const Fragment &f2) const;
};

struct LerpFragment {
    Fragment operator()(const Fragment &a, const Fragment &b, float t) const;
};

struct FragmentTriangle {
    FragmentTriangle(const Fragment &frag1, const Fragment &frag2, const Fragment &frag3);

    Fragment f1, f2, f3;
    [[nodiscard]] std::vector<Fragment> Interpolate() const;

private:
    void scanLineInterpolate(std::vector<Fragment> &fragments, float scanStart, float scanEnd,
                             const Fragment &frag1, const Fragment &frag2, const Fragment &frag3) const;
};
