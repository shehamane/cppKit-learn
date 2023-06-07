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
    T *ptr_;
public:
    explicit Iterator(Iterable<T> *iterable);

    Index index(){
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
