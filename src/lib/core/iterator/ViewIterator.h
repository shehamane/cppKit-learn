#ifndef CPPKIT_LEARN_VIEWITERATOR_H
#define CPPKIT_LEARN_VIEWITERATOR_H

#pragma once

#include <array>

#include "Iterator.h"
#include "../View.h"

template <typename T, std::size_t D>
class ViewIterator : public Iterator<T, D> {
public:
    explicit ViewIterator(Iterable<T, D> *iterable);

    ViewIterator &operator++();

    const ViewIterator operator++(int);
};


#include "ViewIterator.cpp"

#endif //CPPKIT_LEARN_VIEWITERATOR_H
