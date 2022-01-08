#pragma once

#include <memory>
#include "transform/MatrixTransformer/operations/IMatrixOperation.hpp"
#include "core/primitives/Point3f/Point3f.hpp"
#include "core/math/Matrix/Matrix.hpp"
#include "core/math/MathVector/MathVector.hpp"
#include "core/primitives/Normal/Normal.hpp"

class MatrixTransformer {
public:
    MatrixTransformer();
    MatrixTransformer(const MatrixTransformer &transformer) = delete;
    explicit MatrixTransformer(const Matrix<float, 4, 4> &matrix);
    explicit MatrixTransformer(const std::shared_ptr<IMatrixOperation>& o);
    ~MatrixTransformer() = default;

    void ApplyTransforms(MathVector<float, 4> &v) const;
    void ApplyTransforms(Point3f &p) const;
    void ApplyTransforms(Normal &n) const;
    void ResetTransforms();
    void AddOperation(const std::shared_ptr<IMatrixOperation>& o);
    Matrix<float, 4, 4> GetMatrix();

private:
    Matrix<float, 4, 4> transformMatrix;
};
