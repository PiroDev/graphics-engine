#pragma once

#include "lighting/PhongModel/PhongModel.hpp"

#include <memory>

class Material {
public:
    Material(std::shared_ptr<class PhongModel> phongModel, float shininess);

    [[nodiscard]] const std::shared_ptr<class PhongModel> &PhongModel() const;
    std::shared_ptr<class PhongModel> &PhongModel();

    [[nodiscard]] const float &Shininess() const;
    float &Shininess();

private:
    std::shared_ptr<class PhongModel> phongModel;
    float shininess;
};
