#ifndef CPPKIT_LEARN_ITERATOR_H
#define CPPKIT_LEARN_ITERATOR_H

#pragma once

#include <array>

#include "Iterable.h"
#include "Index.h"

template<typename T, std::size_t D>
class Iterator {
protected:
    Iterable<T, D> *iterable_;
    Index<T, D> index_;
    T *ptr_;
public:
    explicit Iterator(Iterable<T, D> *iterable);

    Index<T, D> index(){
        return index_;
    }

    virtual Iterator &operator++() = 0;

    bool operator==(const Iterator &other);

    bool operator!=(const Iterator &other);

    bool operator==(const T *other);

    bool operator!=(const T *other);

    bool operator<=(const T *other);

    T &operator*() const;

    T *operator->() const;
};

#include "Iterator.cpp"

#endif //CPPKIT_LEARN_ITERATOR_H
