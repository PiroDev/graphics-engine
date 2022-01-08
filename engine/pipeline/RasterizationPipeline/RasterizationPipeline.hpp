#pragma once

#include "visibility/DepthTest/ColorBuffer/ColorBuffer.hpp"
#include "visibility/DepthTest/DepthTest.hpp"
#include "scene/Scene.hpp"

struct Viewport {
    float fov = M_PI / 3;
    float width = 2, height = 2;
    float near = 1;
};

class RasterizationPipeline {
public:
    explicit RasterizationPipeline(Viewport viewport = Viewport());

    void operator() (ColorBuffer &colorBuffer, const Scene &scene) const;

private:
    void modelViewTransform(std::shared_ptr<Model> &model, const std::shared_ptr<Camera> &camera) const;
    void projectionTransform(std::shared_ptr<Model> &model, unsigned canvasWidth, unsigned canvasHeight) const;
    std::vector<ProjectedFragment> rasterization(std::shared_ptr<Model> &model, const std::shared_ptr<PointLight> &light,
                                                 const std::shared_ptr<Camera> &camera, unsigned canvasWidth, unsigned canvasHeight) const;
    void visibility(ColorBuffer &colorBuffer, DepthBuffer &depthBuffer, const std::vector<ProjectedFragment> &fragments) const;
    [[nodiscard]] Point3f unProjectPoint(const Point3f &p, float canvasWidth, float canvasHeight) const;

    Viewport viewport;
};
