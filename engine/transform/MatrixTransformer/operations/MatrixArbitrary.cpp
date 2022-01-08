#include "MatrixArbitrary.hpp"

#include <utility>

MatrixArbitrary::MatrixArbitrary(Matrix<float, 4, 4> matrix) : matrix(std::move(matrix)) {}

Matrix<float, 4 ,4> MatrixArbitrary::GetMatrix() {
    return matrix;
}
