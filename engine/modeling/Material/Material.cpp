#include "Material.hpp"

#include <utility>

Material::Material(std::shared_ptr<class PhongModel> phongModel, float shininess)
        : phongModel(std::move(phongModel)), shininess(shininess) {}

std::shared_ptr<class PhongModel> &Material::PhongModel() {
    return phongModel;
}

const std::shared_ptr<class PhongModel> &Material::PhongModel() const {
    return phongModel;
}

const float &Material::Shininess() const {
    return shininess;
}

float &Material::Shininess() {
    return shininess;
}
