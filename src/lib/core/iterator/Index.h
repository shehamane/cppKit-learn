#ifndef CPPKIT_LEARN_INDEX_H
#define CPPKIT_LEARN_INDEX_H

#pragma once

#include <vector>
#include <string>

#include "Iterable.h"

class Index {
private:
    std::vector<std::size_t> index_;
    std::vector<std::size_t> shape_;
public:
    explicit Index(std::vector<size_t> shape);

    explicit Index(std::vector<size_t> shape, std::vector<std::size_t> indices);

    std::vector<std::size_t> indices();

    size_t dims();

    void next();

    void prev();

    void fromFlat();

    std::string toString();
};


#include "Index.cpp"

#endif //CPPKIT_LEARN_INDEX_H
