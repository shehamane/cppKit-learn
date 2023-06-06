#ifndef CPPKIT_LEARN_TENSOR_H
#define CPPKIT_LEARN_TENSOR_H

#pragma once

#include <vector>
#include <array>
#include <iostream>

#include "iterator/Iterable.h"
#include "iterator/Iterator.h"

template<typename T, size_t D>
class View;

template<typename T, size_t D>
class Tensor {
private:
    std::array<size_t, D> shape_;
    std::array<size_t, D> strides_{1};
    std::vector<T> data_;
public:
    template<typename... Dims>
    explicit Tensor(Dims... dims);

    T &operator[](std::array<size_t, D> indices);

    Tensor& operator=(const View<T, D>& view);

    std::array<size_t, D> shape() const;
    
    size_t dims() const;

    std::vector<T> data() const;
};


#include "Tensor.cpp"

#endif //CPPKIT_LEARN_TENSOR_H
