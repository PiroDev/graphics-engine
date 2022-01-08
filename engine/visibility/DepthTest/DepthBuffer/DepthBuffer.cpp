#include "DepthBuffer.hpp"

#include <algorithm>
#include <utility>

DepthBuffer::DepthBuffer(unsigned width, unsigned height, float initValue, std::shared_ptr<IDepthComparator> compare)
        : width(width), height(height), compare(std::move(compare)) {
    auto bufferSize = width * height;
    data = std::shared_ptr<float[]>(new float[bufferSize]());
    std::fill_n(data.get(), bufferSize, initValue);
}

bool DepthBuffer::UpdateDepth(unsigned x, unsigned y, float depth) {
    if (x > width || y > height) {
        return false;
    }

    auto &currentDepth = data[y * width + x];
    bool result = (*compare)(depth, currentDepth);
    if (result) {
        currentDepth = depth;
    }

    return result;
}

unsigned DepthBuffer::Width() const {
    return width;
}

unsigned DepthBuffer::Height() const {
    return height;
}

DepthBuffer::~DepthBuffer() = default;
