#include "Rasterizer.hpp"

#include <array>
#include <algorithm>

bool FragmentsCmpByY::operator()(const Fragment &f1, const Fragment &f2) const {
    return f1.p.Y() < f2.p.Y();
}

Fragment LerpFragment::operator()(const Fragment &a, const Fragment &b, float t) const {
    LerpXYZf lerp;

    auto p = lerp(a.p, b.p, t);
    auto n = lerp(a.n, b.n, t);

    return Fragment{p,n};
}

FragmentTriangle::FragmentTriangle(const Fragment &frag1, const Fragment &frag2, const Fragment &frag3) {
    std::array<Fragment, 3> frags = {frag1, frag2, frag3};
    FragmentsCmpByY compare;
    std::sort(frags.begin(), frags.end(), compare);

    f1 = Fragment(frags[0]);
    f2 = Fragment(frags[1]);
    f3 = Fragment(frags[2]);
}

std::vector<Fragment> FragmentTriangle::Interpolate() const {
    LerpFragment lerpFragment;
    std::vector<Fragment> fragments;

    auto y1 = f1.p.Y();
    auto y2 = f2.p.Y();
    auto y3 = f3.p.Y();

    float fMt = (y2 - y1) / (y3 - y1);
    Fragment fM = lerpFragment(f1, f3, fMt);

    scanLineInterpolate(fragments, y2, y1, f2, fM, f1);
    scanLineInterpolate(fragments, y2, y3, f2, fM, f3);

    return fragments;
}

void FragmentTriangle::scanLineInterpolate(std::vector<Fragment> &fragments, float scanStart, float scanEnd,
                                           const Fragment &fragTop1, const Fragment &fragTop2, const Fragment &fragBot) const {
    LerpFragment lerpFragment;
    float lerpStepY = 1 / std::abs(scanEnd - scanStart);;

    float yT = 0.f;
    while (yT <= 1.f) {
        Fragment fStart = lerpFragment(fragTop1, fragBot, yT);
        Fragment fEnd = lerpFragment(fragTop2, fragBot, yT);

        fragments.push_back(fStart);

        float xStart = fStart.p.X();
        float xEnd = fEnd.p.X();
        if (xStart > xEnd) {
            std::swap(fStart, fEnd);
        }
        float lerpStepX = 1 / std::abs(xEnd - xStart);

        float xT = 0.f;
        while (xT <= 1.f) {
            Fragment f = lerpFragment(fStart, fEnd, xT);
            fragments.push_back(f);

            xT += lerpStepX;
        }

        yT += lerpStepY;
    }
}