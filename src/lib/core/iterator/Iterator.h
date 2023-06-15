#ifndef CPPKIT_LEARN_ITERATOR_H
#define CPPKIT_LEARN_ITERATOR_H

#pragma once

#include <array>

#include "Iterable.h"
#include "Index.h"

template<typename T>
class Iterator {
protected:
    Iterable<T> *iterable_;
    Index index_;
public:
    explicit Iterator(Iterable<T> *iterable, Index index);

    Index index();

    Iterator<T> &operator++();

    T& operator*() const;

    bool operator==(const Iterator &other) const;

    bool operator!=(const Iterator &other) const;

    T &operator*();
};

#include "Iterator.tpp"

#endif //CPPKIT_LEARN_ITERATOR_H
