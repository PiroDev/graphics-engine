#pragma once

#include <memory>
#include "core/primitives/color/ColorRGB.hpp"

class ColorBuffer {
public:
    ColorBuffer(unsigned width, unsigned height);
    ColorBuffer(unsigned width, unsigned height, std::shared_ptr<ColorRGB[]> data);
    void PutPixel(unsigned x, unsigned y, const ColorRGB &color);
    [[nodiscard]] ColorRGB GetPixel(unsigned x, unsigned y) const;
    [[nodiscard]] unsigned Width() const;
    [[nodiscard]] unsigned Height() const;
    std::shared_ptr<ColorRGB[]> Data();

    ~ColorBuffer();

private:
    unsigned width, height;
    std::shared_ptr<ColorRGB[]> data;
};



