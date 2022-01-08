#include "Model.hpp"

std::vector<Point3f> &Model::Points() {
    return geometryModel.Points();
}

const std::vector<Point3f> &Model::Points() const {
    return geometryModel.Points();
}

std::vector<Polygon> &Model::Polygons() {
    return geometryModel.Polygons();
}

const std::vector<Polygon> &Model::Polygons() const {
    return geometryModel.Polygons();
}

std::vector<Normal> &Model::Normals() {
    return geometryModel.Normals();
}

const std::vector<Normal> &Model::Normals() const {
    return geometryModel.Normals();
}

std::shared_ptr<Material> &Model::Material() {
    return material;
}

const std::shared_ptr<Material> &Model::Material() const {
    return material;
}

Matrix<float, 4, 4> &Model::ModelMatrix() {
    return matrix;
}

const Matrix<float, 4, 4> &Model::ModelMatrix() const {
    return matrix;
}

const BrickGenerationParams &Model::GenerationParams() const {
    return generationParams;
}

Model::Model(GeometryModel geometryModel, std::shared_ptr<class Material> material, Matrix<float, 4, 4> modelMatrix,
             const BrickGenerationParams &generationParams)
        : geometryModel(std::move(geometryModel)), material(std::move(material)),
          matrix(std::move(modelMatrix)), generationParams(generationParams) {}
