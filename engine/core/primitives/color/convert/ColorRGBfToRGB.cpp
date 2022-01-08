#include "ColorRGBfToRGB.hpp"

ColorRGB ColorRGBfToRGB::operator()(const ColorRGBf &src) const {
    auto srcR = src.R();
    auto srcG = src.G();
    auto srcB = src.B();

    unsigned char newR = srcR < 1 ? (unsigned char) (srcR * 255) : (unsigned char) 255;
    unsigned char newG = srcG < 1 ? (unsigned char) (srcG * 255) : (unsigned char) 255;
    unsigned char newB = srcB < 1 ? (unsigned char) (srcB * 255) : (unsigned char) 255;

    return {newR, newG, newB};
}
