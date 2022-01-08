#pragma once

class ColorRGB {
public:
    ColorRGB();
    ColorRGB(unsigned char r, unsigned char g, unsigned char b);

    [[nodiscard]] unsigned char R() const;
    unsigned char &R();
    [[nodiscard]] unsigned char G() const;
    unsigned char &G();
    [[nodiscard]] unsigned char B() const;
    unsigned char &B();

private:
    unsigned char r, g, b;
};