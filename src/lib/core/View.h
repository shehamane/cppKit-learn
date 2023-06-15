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
    size_t currDim_;
public:
    View(Tensor<T> &tensor, const std::vector<std::array<size_t, 3>> &slices, size_t currDim = 0);

    View<T> operator[](int index);

    operator T() const;

    T &at(Index index) override;

    [[nodiscard]] bool isOneElement() const;

    [[nodiscard]] std::vector<size_t> shape() const;

    [[nodiscard]] size_t dims() const;

    [[nodiscard]] size_t currDim() const;

    Iterator<T> begin() const override;

    Iterator<T> end() const override;

    Iterator<T> begin() override;

    Iterator<T> end() override;
};

#include "View.tpp"

#endif //CPPKIT_LEARN_VIEW_H
