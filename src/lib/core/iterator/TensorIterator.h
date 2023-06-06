#ifndef CPPKIT_LEARN_TENSORITERATOR_H
#define CPPKIT_LEARN_TENSORITERATOR_H

#pragma once

#include <array>

#include "Iterator.h"
#include "../Tensor.h"

template <typename T, std::size_t D>
class TensorIterator : public Iterator<T, D> {
public:
    explicit TensorIterator(Iterable<T, D> *iterable);

    TensorIterator &operator++();

    const TensorIterator operator++(int);
};

#include "TensorIterator.cpp"

#endif //CPPKIT_LEARN_TENSORITERATOR_H
