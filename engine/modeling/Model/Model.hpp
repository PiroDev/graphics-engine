#pragma once

#include <vector>

#include "core/primitives/Point3f/Point3f.hpp"
#include "core/primitives/Polygon/Polygon.hpp"
#include "core/primitives/Normal/Normal.hpp"
#include "core/math/Matrix/Matrix.hpp"
#include "modeling/Material/Material.hpp"
#include "modeling/BrickGenerator/BrickGenerator.hpp"

class Model {
public:
    Model(GeometryModel geometryModel, std::shared_ptr<Material> material, Matrix<float, 4, 4> modelMatrix,
          const BrickGenerationParams &generationParams);

    Model(const Model &) = default;
    Model(Model &&) = default;
    ~Model() = default;
    Model &operator=(const Model &) = delete;
    Model &operator=(Model &&) = delete;

    std::vector<Point3f> &Points();
    [[nodiscard]] const std::vector<Point3f> &Points() const;

    std::vector<Normal> &Normals();
    [[nodiscard]] const std::vector<Normal> &Normals() const;

    std::vector<Polygon> &Polygons();
    [[nodiscard]] const std::vector<Polygon> &Polygons() const;

    std::shared_ptr<class Material> &Material();
    [[nodiscard]] const std::shared_ptr<class Material> &Material() const;

    Matrix<float, 4, 4> &ModelMatrix();
    [[nodiscard]] const Matrix<float, 4, 4> &ModelMatrix() const;

    [[nodiscard]] const BrickGenerationParams &GenerationParams() const;

private:
    GeometryModel geometryModel;
    std::shared_ptr<class Material> material;
    Matrix<float, 4, 4> matrix;
    BrickGenerationParams generationParams;
};
