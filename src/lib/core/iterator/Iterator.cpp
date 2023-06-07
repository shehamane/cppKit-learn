#include "Iterator.h"

template<typename T>
Iterator<T>::Iterator(Iterable<T> *iterable) :
        iterable_(iterable), index_(Index(iterable->shape())), ptr_(iterable_->start()) {}


template<typename T>
bool Iterator<T>::operator==(const Iterator &other) {
    return ptr_ == other.ptr_;
}

template<typename T>
bool Iterator<T>::operator!=(const Iterator &other) {
    return ptr_ != other.ptr_;
}

template<typename T>
bool Iterator<T>::operator==(const T *other) {
    return ptr_ == other;
}

template<typename T>
bool Iterator<T>::operator!=(const T *other) {
    return ptr_ != other;
}

template<typename T>
bool Iterator<T>::operator<=(const T *other) {
    return ptr_ <= other;
}


template<typename T>
T &Iterator<T>::operator*() const {
    return *ptr_;
}

template<typename T>
T *Iterator<T>::operator->() const {
    return ptr_;
}






