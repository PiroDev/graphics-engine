#pragma once

#include <vector>
#include "core/primitives/Point3f/Point3f.hpp"
#include "core/primitives/Polygon/Polygon.hpp"
#include "core/primitives/Normal/Normal.hpp"

class GeometryModel {
public:
    GeometryModel(std::vector<Point3f> points, std::vector<Normal> normals, std::vector<Polygon> polygons);

    [[nodiscard]] const std::vector<Point3f> &Points() const;
    std::vector<Point3f> &Points();

    [[nodiscard]] const std::vector<Normal> &Normals() const;
    std::vector<Normal> &Normals();

    [[nodiscard]] const std::vector<Polygon> &Polygons() const;
    std::vector<Polygon> &Polygons();

private:
    std::vector<Point3f> points;
    std::vector<Normal> normals;
    std::vector<Polygon> polygons;
};


