#include "PhongFragment.hpp"

PhongFragment::PhongFragment(Point3f position, class Normal normal, const std::shared_ptr<class Material> &material)
        : position(position), normal(normal), material(material) {}

const Point3f &PhongFragment::Position() const {
    return position;
}

Point3f &PhongFragment::Position() {
    return position;
}

const Normal &PhongFragment::Normal() const {
    return normal;
}

Normal &PhongFragment::Normal() {
    return normal;
}

const std::shared_ptr<class Material> &PhongFragment::Material() const {
    return material;
}

