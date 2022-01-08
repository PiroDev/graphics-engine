#include "ColorBuffer.hpp"

#include <utility>

ColorBuffer::ColorBuffer(unsigned width, unsigned height) : width(width), height(height) {
    auto bufferSize = width * height;
    data = std::shared_ptr<ColorRGB[]>(new ColorRGB[bufferSize]());
}

ColorBuffer::ColorBuffer(unsigned width, unsigned height, std::shared_ptr<ColorRGB[]> data) : width(width), height(height),
                                                                                          data(std::move(data)) {}

void ColorBuffer::PutPixel(unsigned x, unsigned y, const ColorRGB &color) {
    if (x > width || y > height) {
        return;
    }

    data[y * width + x] = color;
}

ColorRGB ColorBuffer::GetPixel(unsigned x, unsigned y) const {
    if (x > width || y > height) {
        return {0,0,0};
    }

    return data[y * width + y];
}

unsigned ColorBuffer::Width() const {
    return width;
}

unsigned ColorBuffer::Height() const {
    return height;
}

std::shared_ptr<ColorRGB[]> ColorBuffer::Data() {
    return data;
}

ColorBuffer::~ColorBuffer() = default;
