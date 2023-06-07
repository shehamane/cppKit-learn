#ifndef CPPKIT_LEARN_ITERABLE_H
#define CPPKIT_LEARN_ITERABLE_H

#pragma once

#include <vector>

class Index;

template <typename T>
class Iterable{
public:
    virtual T* start() = 0;
    virtual T* end() = 0;
    virtual std::vector<std::size_t> shape() = 0;
    virtual T& operator[](Index index) = 0;
};

#endif //CPPKIT_LEARN_ITERABLE_H
