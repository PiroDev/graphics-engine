#pragma once

#include <memory>

#include "transform/MatrixTransformer/operations/IMatrixOperation.hpp"
#include "view/Camera/Camera.hpp"
#include "core/primitives/Normal/Normal.hpp"

class MatrixViewTransform : public IMatrixOperation {
public:
    explicit MatrixViewTransform(const std::shared_ptr<Camera> &camera);
    ~MatrixViewTransform() override = default;

    Matrix<float, 4, 4> GetMatrix() override;

private:
    Normal leftAxis;
    Normal forwardAxis;
    Normal upAxis;
    Point3f eye;
};
