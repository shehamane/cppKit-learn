#ifndef CPPKIT_LEARN_INDEX_H
#define CPPKIT_LEARN_INDEX_H

#pragma once

#include <array>
#include <string>

#include "Iterable.h"

template<typename T, std::size_t D>
class Index {
private:
    std::array<std::size_t, D> index_;
    std::array<std::size_t, D> shape_;
    std::size_t dims_;
public:
    explicit Index(Iterable<T, D> *iterable);

    explicit Index(Iterable<T, D> *iterable, std::array<std::size_t, D> indices);

    std::array<std::size_t, D> indices();

    void next();

    void prev();

    void fromFlat();

    std::string toString();
};

#include "Index.cpp"

#endif //CPPKIT_LEARN_INDEX_H
