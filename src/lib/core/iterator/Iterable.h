#ifndef CPPKIT_LEARN_ITERABLE_H
#define CPPKIT_LEARN_ITERABLE_H

#pragma once

#include <vector>
#include <memory>

class Index;

template <typename T>
class Iterator;

template <typename T>
class Iterable{
public:
    virtual Iterator<T> begin() = 0;
    virtual Iterator<T> end() = 0;
    virtual std::vector<std::size_t> shape() const = 0;
    virtual T& operator[](Index index) = 0;
};

#endif //CPPKIT_LEARN_ITERABLE_H
