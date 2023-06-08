#include "Iterator.h"

#include <utility>

template<typename T>
Iterator<T>::Iterator(Iterable<T> *iterable, Index index) :
        iterable_(iterable), index_(std::move(index)) {}


template<typename T>
Index Iterator<T>::index() {
    return index_;
}

template<typename T>
Iterator<T> &Iterator<T>::operator++() {
    index_.next();
    return *this;
}

template<typename T>
bool Iterator<T>::operator==(const Iterator &other) const {
    return index_ == other.index_;
}

template<typename T>
bool Iterator<T>::operator!=(const Iterator &other) const {
    return index_ != other.index_;
}

template<typename T>
T &Iterator<T>::operator*() {
    return iterable_->operator[](index_);
}
