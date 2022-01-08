#include "PointLight.hpp"

#include <utility>

PointLight::PointLight(Point3f pos, std::shared_ptr<class PhongModel> phongModel)
        : position(pos), phongModel(std::move(phongModel)) {}

const Point3f &PointLight::Position() const {
    return position;
}

Point3f &PointLight::Position() {
    return position;
}

std::shared_ptr<class PhongModel> &PointLight::PhongModel() {
    return phongModel;
}

const std::shared_ptr<class PhongModel> &PointLight::PhongModel() const {
    return phongModel;
}
