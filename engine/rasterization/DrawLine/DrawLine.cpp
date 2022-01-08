#include "DrawLine.hpp"

#include <cmath>

void DrawLine::operator()(ColorBuffer &colorBuffer, const Point3f &start, const Point3f &end, const ColorRGB &color) {
    auto width = colorBuffer.Width();
    auto height = colorBuffer.Height();

    int x1 = start.X();
    int x2 = end.X();
    int y1 = start.Y();
    int y2 = end.Y();
    int dx = x2 - x1;
// if x1 == x2, then it does not matter what we set here
    int ix((dx > 0) - (dx < 0));

    dx = std::abs(dx) << 1;

    int dy = y2 - y1;
// if y1 == y2, then it does not matter what we set here
    int iy((dy > 0) - (dy < 0));
    dy = std::abs(dy) << 1;

    colorBuffer.PutPixel(x1, y1, color);

    if (dx >= dy) {
// error may go below zero
        int error(dy - (dx >> 1));

        while (x1 != x2) {
            if ((error >= 0) && (error || (ix > 0))) {
                error -= dx;
                y1 += iy;
            }
// else do nothing

            error += dy;
            x1 += ix;

            colorBuffer.PutPixel(x1, y1, color);
        }
    } else {
// error may go below zero
        int error(dx - (dy >> 1));

        while (y1 != y2) {
            if ((error >= 0) && (error || (iy > 0))) {
                error -= dy;
                x1 += ix;
            }
// else do nothing

            error += dx;
            y1 += iy;
            colorBuffer.PutPixel(x1, y1, color);

        }
    }
}