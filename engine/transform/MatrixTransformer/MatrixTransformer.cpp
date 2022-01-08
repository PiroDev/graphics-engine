#include "MatrixTransformer.hpp"

#include <utility>

MatrixTransformer::MatrixTransformer() : transformMatrix(glm::mat4(1)) {}

void MatrixTransformer::ApplyTransforms(MathVector<float, 4> &v) const {
    v = transformMatrix * v;
}

void MatrixTransformer::ResetTransforms() {
    transformMatrix = Matrix<float, 4, 4>(glm::mat4(1));
}

void MatrixTransformer::AddOperation(const std::shared_ptr<IMatrixOperation>& o) {
    transformMatrix = o->GetMatrix() * transformMatrix;
}

Matrix<float, 4, 4> MatrixTransformer::GetMatrix() {
    return transformMatrix;
}

MatrixTransformer::MatrixTransformer(const Matrix<float, 4, 4> &matrix) : transformMatrix(matrix) {}

void MatrixTransformer::ApplyTransforms(Point3f &point) const {
    MathVector<float, 4> v{{point.X(), point.Y(), point.Z(), 1}};

    v = transformMatrix * v;

    point.X() = v[0];
    point.Y() = v[1];
    point.Z() = v[2];
}

void MatrixTransformer::ApplyTransforms(Normal &n) const {
    MathVector<float, 4> v{{n.X(), n.Y(), n.Z(), 1}};

    v = transformMatrix * v;

    n.X() = v[0];
    n.Y() = v[1];
    n.Z() = v[2];
}

MatrixTransformer::MatrixTransformer(const std::shared_ptr<IMatrixOperation> &o) : transformMatrix(o->GetMatrix()) {}
