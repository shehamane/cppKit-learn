#ifndef CPPKIT_LEARN_TENSOR_H
#define CPPKIT_LEARN_TENSOR_H

#pragma once

#include <vector>
#include <array>
#include <iostream>

#include "iterator/Index.h"

template<typename T, size_t D>
class View;

template<typename T, size_t D>
class Tensor : public Iterable<T, D>{
private:
    std::array<size_t, D> shape_;
    std::vector<T> data_;
public:
    template<typename... Dims>
    explicit Tensor(Dims... dims);

    T &operator[](Index<T, D> index);

    T &operator[](std::array<size_t, D> indices);

    Tensor &operator=(const View<T, D> &view);

    std::array<size_t, D> shape();

    size_t dims() const;

    std::vector<T> data() const;

    T* start();

    T* end();
};

#include "Tensor.cpp"

#endif //CPPKIT_LEARN_TENSOR_H
