#pragma once

#include <initializer_list>
#include <ostream>

#include <glm/matrix.hpp>

template<typename T, unsigned S>
class MathVector {
public:
    MathVector();
    explicit MathVector(const T &initValue);
    MathVector(glm::vec<S, T> vector);
    MathVector(const MathVector &v) noexcept;
    MathVector(MathVector &&v) noexcept;
    MathVector &operator=(const MathVector &v) noexcept;
    MathVector &operator=(MathVector &&v) noexcept;
    ~MathVector() noexcept = default;

public:
    [[nodiscard]] unsigned Size() const noexcept;
    [[nodiscard]] T Length() const;

public:
    T operator*(const MathVector &right) const;
    MathVector operator*(const T &scalar) const;

    MathVector operator&(const MathVector &right) const;

    MathVector operator+(const MathVector &right) const;

    MathVector operator-(const MathVector &right) const;

    MathVector operator-() const;
    T &operator[](unsigned index);
    const T &operator[](unsigned index) const;

    MathVector &operator+=(const MathVector &right);
    MathVector &operator-=(const MathVector &right);

    explicit operator glm::vec<S, T>() const;

private:
    glm::vec<S, T> data;
};

template<typename T, unsigned S>
MathVector<T, S> operator*(const T &scalar, const MathVector<T, S> &v);

template<typename T, unsigned S>
std::ostream &operator<<(std::ostream &os, const MathVector<T, S> &v);

template<typename T, unsigned S>
MathVector<T, S>::MathVector() = default;

template<typename T, unsigned S>
MathVector<T, S>::MathVector(const T &initValue) : data(initValue) {}

template<typename T, unsigned S>
MathVector<T, S>::MathVector(const MathVector &v) noexcept {
    data = v.data;
}

template<typename T, unsigned S>
MathVector<T, S>::MathVector(MathVector &&v) noexcept {
    data = v.data;
}

template<typename T, unsigned S>
MathVector<T, S> &MathVector<T, S>::operator=(const MathVector &v) noexcept {
    if (this != &v) {
        data = v.data;
    }

    return *this;
}

template<typename T, unsigned S>
MathVector<T, S> &MathVector<T, S>::operator=(MathVector &&v) noexcept {
    data = v.data;

    return *this;
}

template<typename T, unsigned S>
T MathVector<T, S>::operator*(const MathVector<T, S> &right) const {
    return {glm::dot(data, right.data)};
}

template<typename T, unsigned S>
MathVector<T, S> MathVector<T, S>::operator&(const MathVector<T, S> &right) const {
    return {glm::cross(data, right.data)};
}

template<typename T, unsigned S>
MathVector<T, S> MathVector<T, S>::operator+(const MathVector<T, S> &right) const {
    return {data + right.data};
}

template<typename T, unsigned S>
MathVector<T, S> MathVector<T, S>::operator-(const MathVector<T, S> &right) const {
    return {data - right.data};
}

template<typename T, unsigned S>
MathVector<T, S> MathVector<T, S>::operator-() const {
    return {-data};
}

template<typename T, unsigned S>
T &MathVector<T, S>::operator[](unsigned index) {
    return data[index];
}

template<typename T, unsigned S>
const T &MathVector<T, S>::operator[](unsigned index) const {
    return data[index];
}

template<typename T, unsigned S>
MathVector<T, S> &MathVector<T, S>::operator+=(const MathVector<T, S> &right) {
    data += right.data;

    return *this;
}

template<typename T, unsigned S>
MathVector<T, S> &MathVector<T, S>::operator-=(const MathVector<T, S> &right) {
    data -= right.data;

    return *this;
}

template<typename T, unsigned S>
unsigned MathVector<T, S>::Size() const noexcept {
    return S;
}

template<typename T, unsigned S>
T MathVector<T, S>::Length() const {
    return glm::length(data);
}

template<typename T, unsigned S>
MathVector<T, S>::MathVector(glm::vec<S, T> vector) : data(std::move(vector)) {}

template<typename T, unsigned S>
MathVector<T, S> MathVector<T, S>::operator*(const T &scalar) const {
    return {data * scalar};
}

template<typename T, unsigned S>
MathVector<T, S> operator*(const T &scalar, const MathVector<T, S> &v) {
    return v * scalar;
}

template<typename T, unsigned S>
MathVector<T, S>::operator glm::vec<S, T>() const {
    return data;
}


template<typename T, unsigned S>
std::ostream &operator<<(std::ostream &os, const MathVector<T, S> &v) {
    os << "[";
    for (auto i = 0; i < v.Size(); i++) {
        os << v[i];
        if (i != v.Size() - 1) {
            os << ", ";
        }
    }
    os << "]";

    return os;
}

