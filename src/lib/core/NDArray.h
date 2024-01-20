#ifndef CPPKIT_LEARN_ITERABLE_H
#define CPPKIT_LEARN_ITERABLE_H

#pragma once

#include <vector>
#include <memory>
#include <iostream>

class Index;

template<typename T>
class Iterator;

template<typename T>
class NDArray {
public:
    virtual Iterator<T> begin() = 0;

    virtual Iterator<T> end() = 0;

    virtual Iterator<T> begin() const = 0;

    virtual Iterator<T> end() const = 0;

    [[nodiscard]] virtual std::vector<std::size_t> shape() const = 0;

    virtual T at(Index index) const = 0;

    virtual T &operator[](Index index) = 0;

    virtual std::vector<T> data() const = 0;

    template<typename Y>
    friend std::ostream &operator<<(std::ostream &os, const NDArray<Y> &tensor);
};

#include "NDarray.tpp"

#endif //CPPKIT_LEARN_ITERABLE_H
