#include "PhongModel.hpp"

PhongModel::PhongModel(ColorRGBf ambient, ColorRGBf diffuse, ColorRGBf specular)
        : ambient(ambient), diffuse(diffuse), specular(specular) {}


ColorRGBf &PhongModel::Ambient() {
    return ambient;
}

const ColorRGBf &PhongModel::Ambient() const {
    return ambient;
}

ColorRGBf &PhongModel::Diffuse() {
    return diffuse;
}

const ColorRGBf &PhongModel::Diffuse() const {
    return diffuse;
}

ColorRGBf &PhongModel::Specular() {
    return specular;
}

const ColorRGBf &PhongModel::Specular() const {
    return specular;
}

