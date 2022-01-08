#include "DepthTest.hpp"


void DepthTest::operator()(ColorBuffer &colorBuffer, DepthBuffer &depthBuffer,
                           const std::vector<ProjectedFragment> &fragments) {
    if (colorBuffer.Width() != depthBuffer.Width() ||
        colorBuffer.Height() != depthBuffer.Height()) {
        return;
    }

    auto width = colorBuffer.Width();
    auto height = colorBuffer.Height();

    for (const auto &fragment: fragments) {
        if (fragment.X() > width || fragment.Y() > height) {
            continue;
        }

        auto x = fragment.X();
        auto y = fragment.Y();
        auto depth = fragment.Depth();

        if (depthBuffer.UpdateDepth(x, y, depth)) {
            auto color = fragment.Color();
            colorBuffer.PutPixel(x, y, color);
        }
    }
}
