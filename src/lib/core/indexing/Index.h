#ifndef CPPKIT_LEARN_INDEX_H
#define CPPKIT_LEARN_INDEX_H

#pragma once

#include <vector>
#include <string>

#include "../NDArray.h"

class Index {
private:
    std::vector<std::size_t> indices_;
    std::vector<std::size_t> shape_;
public:
    Index(std::vector<size_t> shape);

    explicit Index(std::vector<size_t> shape, std::vector<std::size_t> indices);

    explicit Index(std::vector<size_t> shape, std::initializer_list<int> indices);

//    explicit Index(std::vector<size_t> shape, unsigned int index);

    std::vector<std::size_t> indices();

    size_t dims();

    void next();

    void prev();

    size_t toFlat();

    std::string toString();

    bool operator==(const Index& other) const;

    bool operator!=(const Index& other) const;

    bool isOut();

    static Index begin(const std::vector<size_t>& shape);

    static Index end(const std::vector<size_t>& shape);

    size_t &operator[](int i);
};


#endif //CPPKIT_LEARN_INDEX_H
