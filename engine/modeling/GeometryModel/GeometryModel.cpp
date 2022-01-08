#include "GeometryModel.hpp"

GeometryModel::GeometryModel(std::vector<Point3f> points, std::vector<Normal> normals, std::vector<Polygon> polygons)
        : points(std::move(points)), polygons(std::move(polygons)), normals(std::move(normals)) {}

const std::vector<Point3f> &GeometryModel::Points() const {
    return points;
}

std::vector<Point3f> &GeometryModel::Points() {
    return points;
}

const std::vector<Polygon> &GeometryModel::Polygons() const {
    return polygons;
}

std::vector<Polygon> &GeometryModel::Polygons() {
    return polygons;
}

const std::vector<Normal> &GeometryModel::Normals() const {
    return normals;
}

std::vector<Normal> &GeometryModel::Normals() {
    return normals;
}