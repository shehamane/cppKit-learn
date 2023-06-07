#ifndef CPPKIT_LEARN_INDEX_H
#define CPPKIT_LEARN_INDEX_H

#pragma once

#include <vector>
#include <string>

#include "Iterable.h"

template<typename T>
class Index {
private:
    std::vector<std::size_t> index_;
    std::vector<std::size_t> shape_;
    std::size_t dims_;
public:
    explicit Index(Iterable<T> *iterable);

    explicit Index(Iterable<T> *iterable, std::vector<std::size_t> indices);

    std::vector<std::size_t> indices();

    void next();

    void prev();

    void fromFlat();

    std::string toString();
};

#include "Index.cpp"

#endif //CPPKIT_LEARN_INDEX_H
