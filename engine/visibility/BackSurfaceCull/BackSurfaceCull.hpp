#pragma once

#include "modeling/Model/Model.hpp"

struct BackSurfaceCull {
    void operator()(std::shared_ptr<Model> &model, const Point3f &eye) const;
};
