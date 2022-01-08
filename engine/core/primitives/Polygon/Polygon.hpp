#pragma once

#include <vector>

class Polygon {
public:
    Polygon();
    Polygon(std::vector<unsigned> p, std::vector<unsigned> n);

    [[nodiscard]] const std::vector<unsigned> &Points() const;
    std::vector<unsigned> &Points();

    [[nodiscard]] const std::vector<unsigned> &Normals() const;
    std::vector<unsigned> &Normals();

private:
    std::vector<unsigned> points;
    std::vector<unsigned> normals;
};
