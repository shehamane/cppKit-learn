#ifndef CPPKIT_LEARN_TENSOR_H
#define CPPKIT_LEARN_TENSOR_H

#pragma once

#include <vector>
#include <array>
#include <iostream>
#include <optional>

#include "iterator/Index.h"
#include "iterator/Iterator.h"

template<typename T>
class View;

template<typename T>
class Tensor : public Iterable<T> {
private:
    std::vector<size_t> shape_;
    std::vector<T> data_;
public:
    explicit Tensor(std::vector<std::size_t> shape);

    Tensor(View<T> &view);

    T &operator[](Index index);

    T &operator[](const std::vector<int> &indices);

    View<T> operator[](const std::vector<std::array<std::optional<int>, 3>> &slices);

    View<T> operator[](int index);

    View<T> slice(const std::vector<std::array<size_t, 3>> &slices);

    [[nodiscard]] std::vector<size_t> shape() const;

    [[nodiscard]] size_t dims() const;

    std::vector<T> data() const;

    [[nodiscard]] size_t size() const;

    Iterator<T> begin();

    Iterator<T> end();
};


#include "Tensor.cpp"

#endif //CPPKIT_LEARN_TENSOR_H
