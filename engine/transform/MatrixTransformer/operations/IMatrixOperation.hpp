#pragma once

#include "core/math/Matrix/Matrix.hpp"

class IMatrixOperation {
public:
    virtual Matrix<float, 4, 4> GetMatrix() = 0;
    virtual ~IMatrixOperation() = default;
};
