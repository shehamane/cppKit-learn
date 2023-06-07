#ifndef CPPKIT_LEARN_VIEW_H
#define CPPKIT_LEARN_VIEW_H

#pragma once

#include <vector>
#include <array>

#include "Tensor.h"

template<typename T>
class View : public Iterable<T> {
private:
    Tensor<T> &tensor_;
    std::vector<size_t> starts_;
    std::vector<size_t> ends_;
    std::vector<size_t> steps_;
    std::vector<size_t> shape_;
public:
    View(Tensor<T> &tensor, const std::vector<std::array<size_t, 3>>& slices);

    T &operator[](Index<T> index);

    std::vector<size_t> shape();

    size_t dims();

    T* start();

    T* end();
};

#include "View.cpp"

#endif //CPPKIT_LEARN_VIEW_H
