#ifndef CPPKIT_LEARN_TENSORITERATOR_H
#define CPPKIT_LEARN_TENSORITERATOR_H

#pragma once


#include "Iterator.h"
#include "../Tensor.h"

template <typename T>
class TensorIterator : public Iterator<T> {
public:
    explicit TensorIterator(Iterable<T> *iterable);

    TensorIterator &operator++();

    const TensorIterator operator++(int);
};

#include "TensorIterator.cpp"

#endif //CPPKIT_LEARN_TENSORITERATOR_H
