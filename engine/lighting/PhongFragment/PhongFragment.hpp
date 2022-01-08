#pragma once

#include "modeling/Material/Material.hpp"
#include "core/primitives/Point3f/Point3f.hpp"
#include "core/primitives/Normal/Normal.hpp"

class PhongFragment {
public:
    PhongFragment(Point3f position, class Normal normal, const std::shared_ptr<class Material> &material);

    [[nodiscard]] const Point3f &Position() const;
    Point3f &Position();
    [[nodiscard]] const class Normal &Normal() const;
    class Normal &Normal();

    [[nodiscard]] const std::shared_ptr<class Material> &Material() const;

private:
    Point3f position;
    class Normal normal;
    const std::shared_ptr<class Material> &material;
};

