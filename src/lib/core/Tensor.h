#ifndef CPPKIT_LEARN_TENSOR_H
#define CPPKIT_LEARN_TENSOR_H

#pragma once

#include <vector>
#include <array>
#include <iostream>

#include "iterator/Index.h"
#include "iterator/Iterator.h"

template<typename T>
class View;

template<typename T>
class Tensor : public Iterable<T> {
private:
    const std::vector<size_t> shape_;
    std::vector<T> data_;
public:
    explicit Tensor(std::vector<std::size_t> shape);

    Tensor(const View<T> &view);

    T &operator[](Index index);

    T &operator[](std::vector<size_t> indices);

    std::vector<size_t> shape() const;

    size_t dims() const;

    std::vector<T> data() const;

    size_t size() const;

    Iterator<T> begin();

    Iterator<T> end();
};


#include "Tensor.cpp"

#endif //CPPKIT_LEARN_TENSOR_H
