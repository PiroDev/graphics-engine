#pragma once

#include <initializer_list>
#include <ostream>
#include "core/math/MathVector/MathVector.hpp"

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_access.hpp>

template<typename T, unsigned R, unsigned C>
class Matrix {
public:
    Matrix() = default;
    explicit Matrix(glm::mat<C, R, T> matrix);
    Matrix(const Matrix &) noexcept;
    Matrix(Matrix &&) noexcept;
    Matrix &operator=(const Matrix &) noexcept;
    Matrix &operator=(Matrix &&) noexcept;
    ~Matrix() noexcept = default;

public:
    [[nodiscard]] unsigned CountColumns() const noexcept;
    [[nodiscard]] unsigned CountRows() const noexcept;
    MathVector<T, R> Column(unsigned index) const;
    MathVector<T, C> Row(unsigned index) const;
    T &Element(unsigned rowIndex, unsigned columnIndex);
    const T &Element(unsigned rowIndex, unsigned columnIndex) const;
    void LoadIdentity();
    Matrix<T, C, R> Transposed() const;
    Matrix Inversed() const;

    explicit operator glm::mat<C, R, T>() const;

public:
    template<unsigned C2>
    Matrix<T, R, C2> operator*(const Matrix<T, C, C2> &right) const;

    MathVector<T, R> operator*(const MathVector<T, R> &right) const;

    Matrix operator*(const T &value) const;

    Matrix operator+(const Matrix &right) const;

    Matrix operator-(const Matrix &right) const;

    Matrix operator-() const;

    template<unsigned C2>
    Matrix<T, R, C2> &operator*=(const Matrix<T, C, C2> &right);
    Matrix<T, R, C> &operator+=(const Matrix<T, R, C> &right);

    Matrix &operator-=(const Matrix &right);

private:
    glm::mat<C, R, T> data;
};

template<typename T, unsigned R, unsigned C>
Matrix<T, R, C> operator*(const T &scalar, const Matrix<T, R, C> &right);

template<typename T, unsigned R, unsigned C>
MathVector<T, C> operator*(const MathVector<T, R> &left, const Matrix<T, R, C> &right);

template<typename T, unsigned R, unsigned C>
std::ostream &operator<<(std::ostream &os, const Matrix<T, R, C> &m);

template<typename T, unsigned R, unsigned C>
Matrix<T, R, C>::Matrix(Matrix &&m) noexcept : data(m.data) {}

#include <iostream>

template<typename T, unsigned R, unsigned C>
Matrix<T, R, C>::Matrix(glm::mat<C, R, T> matrix) : data(std::move(matrix)) {}

template<typename T, unsigned R, unsigned C>
Matrix<T, R, C> &Matrix<T, R, C>::operator=(const Matrix &m) noexcept {
    if (*this != m) {
        data = m.data;
    }

    return *this;
}

template<typename T, unsigned R, unsigned C>
Matrix<T, R, C> &Matrix<T, R, C>::operator=(Matrix &&m) noexcept {
    data = m.data;

    return *this;
}

template<typename T, unsigned R, unsigned C>
Matrix<T, R, C>::Matrix(const Matrix &m) noexcept {
    data = m.data;
}

template<typename T, unsigned R, unsigned C>
unsigned Matrix<T, R, C>::CountColumns() const noexcept {
    return C;
}

template<typename T, unsigned R, unsigned C>
unsigned Matrix<T, R, C>::CountRows() const noexcept {
    return R;
}

template<typename T, unsigned R, unsigned C>
template<unsigned C2>
Matrix<T, R, C2> Matrix<T, R, C>::operator*(const Matrix<T, C, C2> &right) const {
    return Matrix<T, R, C2>(data * right.data);
}

template<typename T, unsigned R, unsigned C>
Matrix<T, R, C> Matrix<T, R, C>::operator+(const Matrix<T, R, C> &right) const {
    return Matrix<T, R, C>(data + right.data);
}

template<typename T, unsigned R, unsigned C>
Matrix<T, R, C> Matrix<T, R, C>::operator-(const Matrix<T, R, C> &right) const {
    return Matrix<T, R, C>(data - right.data);
}

template<typename T, unsigned R, unsigned C>
Matrix<T, R, C> Matrix<T, R, C>::operator-() const {
    return Matrix<T, R, C>(-data);
}

template<typename T, unsigned R, unsigned C>
template<unsigned C2>
Matrix<T, R, C2> &Matrix<T, R, C>::operator*=(const Matrix<T, C, C2> &right) {
    data *= right.data;

    return *this;
}

template<typename T, unsigned R, unsigned C>
Matrix<T, R, C> &Matrix<T, R, C>::operator+=(const Matrix<T, R, C> &right) {
    data += right.data;

    return *this;
}

template<typename T, unsigned R, unsigned C>
Matrix<T, R, C> &Matrix<T, R, C>::operator-=(const Matrix<T, R, C> &right) {
    data -= right.data;

    return *this;
}

template<typename T, unsigned R, unsigned C>
MathVector<T, R> Matrix<T, R, C>::Column(unsigned index) const {
    return {glm::column(data, index)};
}

template<typename T, unsigned R, unsigned C>
MathVector<T, C> Matrix<T, R, C>::Row(unsigned index) const {
    return {glm::row(data, index)};
}

template<typename T, unsigned R, unsigned C>
T &Matrix<T, R, C>::Element(unsigned rowIndex, unsigned columnIndex) {
    return data[columnIndex][rowIndex];
}

template<typename T, unsigned R, unsigned C>
const T &Matrix<T, R, C>::Element(unsigned rowIndex, unsigned columnIndex) const {
    return data[columnIndex][rowIndex];
}


template<typename T, unsigned R, unsigned C>
void Matrix<T, R, C>::LoadIdentity() {
    data = glm::mat<C, R, T>(1);
}

template<typename T, unsigned R, unsigned C>
Matrix<T, C, R> Matrix<T, R, C>::Transposed() const {
    return Matrix<T, R, C>(glm::transpose(data));
}

template<typename T, unsigned R, unsigned C>
Matrix<T, R, C> Matrix<T, R, C>::Inversed() const {
    return Matrix<T, R, C>(glm::inverse(data));
}

template<typename T, unsigned R, unsigned C>
Matrix<T, R, C> Matrix<T, R, C>::operator*(const T &value) const {
    return Matrix<T, R, C>(data * value);
}

template<typename T, unsigned R, unsigned C>
Matrix<T, R, C> operator*(const T &scalar, const Matrix<T, R, C> &right) {
    return right * scalar;
}

template<typename T, unsigned R, unsigned C>
std::ostream &operator<<(std::ostream &os, const Matrix<T, R, C> &m) {
    for (auto i = 0; i < m.CountRows(); i++) {
        os << m.Row(i) << std::endl;
    }

    return os;
}

template<typename T, unsigned R, unsigned C>
Matrix<T, R, C>::operator glm::mat<C, R, T>() const {
    return data;
}

template<typename T, unsigned R, unsigned C>
MathVector<T, R> Matrix<T, R, C>::operator*(const MathVector<T, R> &right) const {
    return {data * (glm::vec<R, T>)right};
}

template<typename T, unsigned R, unsigned C>
MathVector<T, C> operator*(const MathVector<T, R> &left, const Matrix<T, R, C> &right) {
    return {(glm::vec<R, T>)left * (glm::mat<C, R, T>)right};
}
