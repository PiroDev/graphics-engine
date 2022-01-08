#pragma once

#include "core/primitives/Point3f/Point3f.hpp"
#include "lighting/PhongModel/PhongModel.hpp"

#include <memory>

class PointLight {
public:
    PointLight(Point3f pos, std::shared_ptr<class PhongModel> phongModel);

    [[nodiscard]] const Point3f &Position() const;
    Point3f &Position();

    [[nodiscard]] const std::shared_ptr<class PhongModel> &PhongModel() const;
    std::shared_ptr<class PhongModel> &PhongModel();

private:
    Point3f position;
    std::shared_ptr<class PhongModel> phongModel;
};
