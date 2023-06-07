#ifndef CPPKIT_LEARN_TENSOR_H
#define CPPKIT_LEARN_TENSOR_H

#pragma once

#include <vector>
#include <iostream>

#include "iterator/Index.h"

//template<typename T>
//class View;

template<typename T>
class Tensor : public Iterable<T>{
private:
    std::vector<size_t> shape_;
    std::vector<T> data_;
public:
    explicit Tensor(std::vector<std::size_t> shape);

    T &operator[](Index index);

    T &operator[](std::vector<size_t> indices);

    //Tensor &operator=(const View<T> &view);

    std::vector<size_t> shape();

    size_t dims() const;

    std::vector<T> data() const;

    T* start();

    T* end();
};

#include "Tensor.cpp"

#endif //CPPKIT_LEARN_TENSOR_H
