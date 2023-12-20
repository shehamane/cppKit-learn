#ifndef CPPKIT_LEARN_ITERABLE_H
#define CPPKIT_LEARN_ITERABLE_H

#pragma once

#include <vector>
#include <memory>

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

    virtual T &at(Index index) = 0;
};

#endif //CPPKIT_LEARN_ITERABLE_H
