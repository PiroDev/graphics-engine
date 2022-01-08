#include "ColorRGB.hpp"

ColorRGB::ColorRGB() : r(0), g(0), b(0) {}

ColorRGB::ColorRGB(unsigned char r, unsigned char g, unsigned char b) :
        r(r), g(g), b(b) {}

unsigned char ColorRGB::R() const {
    return r;
}

unsigned char &ColorRGB::R() {
    return r;
}

unsigned char ColorRGB::G() const {
    return g;
}

unsigned char &ColorRGB::G() {
    return g;
}

unsigned char ColorRGB::B() const {
    return b;
}

unsigned char &ColorRGB::B() {
    return b;
}
