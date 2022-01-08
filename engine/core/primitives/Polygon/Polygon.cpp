#include "Polygon.hpp"

Polygon::Polygon() = default;

Polygon::Polygon(std::vector<unsigned> p, std::vector<unsigned> n) :
points(std::move(p)), normals(std::move(n)) {}

const std::vector<unsigned> &Polygon::Points() const {
    return points;
}

std::vector<unsigned> &Polygon::Points() {
    return points;
}

const std::vector<unsigned> &Polygon::Normals() const {
    return normals;
}

std::vector<unsigned> &Polygon::Normals() {
    return normals;
}
