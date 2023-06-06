#ifndef CPPKIT_LEARN_ITERABLE_H
#define CPPKIT_LEARN_ITERABLE_H

#pragma once

#include <array>

template <typename T, std::size_t D>
class Iterable{
public:
    virtual T* start() = 0;
    virtual T* end() = 0;
    virtual std::array<std::size_t, D> shape() = 0;
};

#endif //CPPKIT_LEARN_ITERABLE_H
