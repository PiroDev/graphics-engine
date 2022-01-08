#pragma once

#include "visibility/DepthTest/IDepthComparator.hpp"
#include <memory>

class DepthBuffer {
public:
    DepthBuffer(unsigned width, unsigned height, float initValue, std::shared_ptr<IDepthComparator> compare);

    bool UpdateDepth(unsigned x, unsigned y, float depth);
    [[nodiscard]] unsigned Width() const;
    [[nodiscard]] unsigned Height() const;

    ~DepthBuffer();

private:
    std::shared_ptr<IDepthComparator> compare;
    unsigned width, height;
    std::shared_ptr<float[]> data;
};
