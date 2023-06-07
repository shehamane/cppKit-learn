#ifndef CPPKIT_LEARN_VIEWITERATOR_H
#define CPPKIT_LEARN_VIEWITERATOR_H

#pragma once

#include "Iterator.h"
#include "../View.h"

template <typename T>
class ViewIterator : public Iterator<T> {
public:
    explicit ViewIterator(Iterable<T> *iterable);

    ViewIterator &operator++();

    const ViewIterator operator++(int);
};


#include "ViewIterator.cpp"

#endif //CPPKIT_LEARN_VIEWITERATOR_H
