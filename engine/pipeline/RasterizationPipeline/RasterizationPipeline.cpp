#include <projection/MatrixPerspectiveProjection/MatrixPerspectiveProjection.hpp>
#include <view/MatrixViewportToCanvas/MatrixViewportToCanvas.hpp>
#include <shading/PhongShader/PhongShader.hpp>
#include <rasterization/Rasterizer/Rasterizer.hpp>
#include <core/primitives/color/convert/ColorRGBfToRGB.hpp>
#include <visibility/DepthTest/comparator/DepthComparatorNegInf/DepthComparatorNegInf.hpp>
#include <projection/MatrixCanvasToScreen/MatrixCanvasToScreen.hpp>
#include "transform/MatrixTransformer/MatrixTransformer.hpp"
#include "view/MatrixViewTransform/MatrixViewTransform.hpp"
#include "RasterizationPipeline.hpp"
#include "transform/MatrixTransformer/operations/MatrixArbitrary.hpp"
#include "rasterization/DrawLine/DrawLine.hpp"
#include "visibility/BackSurfaceCull/BackSurfaceCull.hpp"

#include <iostream>

void RasterizationPipeline::operator()(ColorBuffer &colorBuffer, const Scene &scene) const {
    const auto &models = scene.Models();
    const auto &camera = scene.Camera();
    auto &light = scene.Light();
    light->Position() = camera->EyePosition();

    auto width = colorBuffer.Width();
    auto height = colorBuffer.Height();

    auto depthComparator = std::make_shared<DepthComparatorNegInf>();
    float limit = -std::numeric_limits<float>::infinity();
    DepthBuffer depthBuffer(width, height, limit, depthComparator);
    BackSurfaceCull backSurfaceCull;

    for (auto &model: models) {
        GeometryModel geometryModel(model->Points(), model->Normals(), model->Polygons());
        auto m = std::make_shared<Model>(geometryModel, model->Material(), model->ModelMatrix(), model->GenerationParams());

        modelViewTransform(m, camera);

        backSurfaceCull(m, {0, 0, 0});

        projectionTransform(m, width, height);

        auto fragments = rasterization(m, light, camera, width, height);

        visibility(colorBuffer, depthBuffer, fragments);
    }

    float near = viewport.near;
    auto fov = viewport.fov;
    auto viewportWidth = viewport.width;
    auto viewportHeight = viewport.height;


    DrawLine drawLine;
    for (auto ind = 0; ind < models.size(); ind++) {
        if (!scene.WireFramed()[ind]) {
            continue;
        }

        auto model = models[ind];
        auto pointsCopy = std::vector<Point3f>(model->Points());
        MatrixTransformer modelPointsTransformer;

        auto modelTransform = std::make_shared<MatrixArbitrary>(model->ModelMatrix());
        auto viewTransform = std::make_shared<MatrixViewTransform>(camera);
        auto viewportToCanvas = std::make_shared<MatrixViewportToCanvas>(fov, viewportWidth, viewportHeight,
                                                                         width, height);

        modelPointsTransformer.AddOperation(modelTransform);
        modelPointsTransformer.AddOperation(viewTransform);
        modelPointsTransformer.AddOperation(viewportToCanvas);

        for (auto &p: pointsCopy) {
            modelPointsTransformer.ApplyTransforms(p);

            MatrixTransformer projectTransformer;
            auto projection = std::make_shared<MatrixPerspectiveProjection>(viewport.near, p.Z());
            auto canvasToScreen = std::make_shared<MatrixCanvasToScreen>(width, height);
            projectTransformer.AddOperation(projection);
            projectTransformer.AddOperation(canvasToScreen);

            projectTransformer.ApplyTransforms(p);
        }

        for (const auto &p: model->Polygons()) {
            auto p1 = pointsCopy[p.Points()[0]];
            auto p2 = pointsCopy[p.Points()[1]];
            auto p3 = pointsCopy[p.Points()[2]];
            drawLine(colorBuffer, p1, p2);
            drawLine(colorBuffer, p1, p3);
            drawLine(colorBuffer, p2, p3);
        }
    }
}

void RasterizationPipeline::modelViewTransform(std::shared_ptr<Model> &model,
                                               const std::shared_ptr<Camera> &camera) const {
    MatrixTransformer pointsTransformer;
    auto viewTransform = std::make_shared<MatrixViewTransform>(camera);
    auto modelTransform = std::make_shared<MatrixArbitrary>(model->ModelMatrix());
    pointsTransformer.AddOperation(modelTransform);
    pointsTransformer.AddOperation(viewTransform);

    for (auto &p: model->Points()) {
        pointsTransformer.ApplyTransforms(p);
    }

    MatrixTransformer normalsTransformer(pointsTransformer.GetMatrix().Transposed().Inversed());
    for (auto &n: model->Normals()) {
        normalsTransformer.ApplyTransforms(n);
    }
}

void RasterizationPipeline::projectionTransform(std::shared_ptr<Model> &model, unsigned canvasWidth,
                                                unsigned canvasHeight) const {
    /* Projection */
    float near = viewport.near;
    auto fov = viewport.fov;
    auto viewportWidth = viewport.width;
    auto viewportHeight = viewport.height;

    /* Viewport -> Canvas */
    auto viewportToCanvas = std::make_shared<MatrixViewportToCanvas>(fov, viewportWidth, viewportHeight,
                                                                     canvasWidth, canvasHeight);

    MatrixTransformer viewportToCanvasTransformer(viewportToCanvas);

    for (auto &p: model->Points()) {
        auto projection = std::make_shared<MatrixPerspectiveProjection>(near, p.Z());
        MatrixTransformer projectionTransformer(projection);
        viewportToCanvasTransformer.ApplyTransforms(p);
        projectionTransformer.ApplyTransforms(p);
    }
}

void roundPoint(Point3f &p) {
    p.X() = std::roundf(p.X());
    p.Y() = std::roundf(p.Y());
}

std::vector<ProjectedFragment> RasterizationPipeline::rasterization(std::shared_ptr<Model> &model,
                                                                    const std::shared_ptr<PointLight> &light,
                                                                    const std::shared_ptr<Camera> &camera, unsigned canvasWidth,
                                                                    unsigned canvasHeight) const {
    std::vector<ProjectedFragment> projectedFragments;


    auto viewTransform = std::make_shared<MatrixViewTransform>(camera);
    MatrixTransformer lightTransformer;
    lightTransformer.AddOperation(viewTransform);
    auto oldLightPos = light->Position();
    lightTransformer.ApplyTransforms(light->Position());

    PhongShader phongShader;
    const auto &polygons = model->Polygons();
    const auto &points = model->Points();
    const auto &normals = model->Normals();
    auto material = model->Material();

    auto viewN = Normal(camera->LookAtPosition(), camera->EyePosition());

    auto canvasToScreen = std::make_shared<MatrixCanvasToScreen>(canvasWidth, canvasHeight);
    MatrixTransformer canvasToScreenTransformer(canvasToScreen);

    for (const auto &p: polygons) {
        auto f1 = Fragment{points[p.Points()[0]], normals[p.Normals()[0]]};
        auto f2 = Fragment{points[p.Points()[1]], normals[p.Normals()[1]]};
        auto f3 = Fragment{points[p.Points()[2]], normals[p.Normals()[2]]};

        roundPoint(f1.p);
        roundPoint(f2.p);
        roundPoint(f3.p);

        FragmentTriangle fragmentTriangle(f1, f2, f3);
        auto fragments = fragmentTriangle.Interpolate();

        for (auto &f: fragments) {
            auto screenPos = f.p;
            canvasToScreenTransformer.ApplyTransforms(screenPos);

            auto x = std::lroundf(screenPos.X());
            auto y = std::lroundf(screenPos.Y());
            float z = screenPos.Z();

            ColorRGBfToRGB rgBfToRgb;

            f.p = unProjectPoint(f.p, (float) canvasWidth, (float) canvasHeight);

            PhongFragment phongFragment(f.p, f.n, material);
            auto fragColor = rgBfToRgb(phongShader(light, phongFragment, viewN));
            ProjectedFragment projectedFragment(x, y, z, fragColor);

            projectedFragments.push_back(projectedFragment);
        }
    }

    light->Position() = oldLightPos;

    return projectedFragments;
}

Point3f RasterizationPipeline::unProjectPoint(const Point3f &p, float canvasWidth, float canvasHeight) const {
    float near = viewport.near;
    auto fov = viewport.fov;
    auto viewportWidth = viewport.width;
    auto viewportHeight = viewport.height;

    float xScale = canvasWidth / viewportWidth;
    float yScale = canvasHeight / viewportHeight;

    Point3f res{};
    res.X() = p.X() * std::abs(p.Z()) / (xScale * near);
    res.Y() = p.Y() * std::abs(p.Z()) / (yScale * near);
    res.Z() = p.Z();

//    auto viewportToCanvas = std::make_shared<MatrixViewportToCanvas>(fov, viewportWidth, viewportHeight,
//                                                                     canvasWidth, canvasHeight);
//    auto projection = std::make_shared<MatrixPerspectiveProjection>(near, p.Z());
//    MatrixInverse inverse;
//    MatrixTransformer transformer;
//    transformer.AddOperation(viewportToCanvas);
//    transformer.AddOperation(projection);
//
//    MatrixTransformer inverseTransformer(inverse(transformer.GetMatrix()));
//    auto unProjected = p;
//    inverseTransformer.ApplyTransforms(unProjected);

    return res;
}

void RasterizationPipeline::visibility(ColorBuffer &colorBuffer, DepthBuffer &depthBuffer,
                                       const std::vector<ProjectedFragment> &fragments) const {
    DepthTest depthTest;
    depthTest(colorBuffer, depthBuffer, fragments);
}

RasterizationPipeline::RasterizationPipeline(Viewport viewport) : viewport(viewport) {}
