#include "BackSurfaceCull.hpp"

void BackSurfaceCull::operator()(std::shared_ptr<Model> &model, const Point3f &eye) const {
    std::vector<Polygon> remaining;

    const auto &polygons = model->Polygons();
    const auto &points = model->Points();
    const auto &normals = model->Normals();

    for (const auto &polygon: model->Polygons()) {
        bool isCulled = true;
        const auto &pPos = polygon.Points();
        const auto &nPos = polygon.Normals();

        for (auto i = 0; i < pPos.size() && isCulled; i++) {
            auto p = points[pPos[i]];
            auto n = normals[nPos[i]];
            auto eyePointVec = Normal(p, eye);
            if (n * eyePointVec >= 0) {
                isCulled = false;
            }
        }

        if (!isCulled) {
            remaining.push_back(polygon);
        }
    }

    model->Polygons() = remaining;
}
