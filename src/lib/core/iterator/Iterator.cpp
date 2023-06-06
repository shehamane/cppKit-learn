#include "Iterator.h"

template<typename T, std::size_t D>
Iterator<T, D>::Iterator(Iterable<T, D> *iterable) :
        iterable_(iterable), index_(Index<T, D>(iterable)), ptr_(iterable_->start()) {}


template<typename T, std::size_t D>
bool Iterator<T, D>::operator==(const Iterator &other) {
    return ptr_ == other.ptr_;
}

template<typename T, std::size_t D>
bool Iterator<T, D>::operator!=(const Iterator &other) {
    return ptr_ != other.ptr_;
}

template<typename T, std::size_t D>
bool Iterator<T, D>::operator==(const T *other) {
    return ptr_ == other;
}

template<typename T, std::size_t D>
bool Iterator<T, D>::operator!=(const T *other) {
    return ptr_ != other;
}

template<typename T, std::size_t D>
bool Iterator<T, D>::operator<=(const T *other) {
    return ptr_ <= other;
}


template<typename T, std::size_t D>
T &Iterator<T, D>::operator*() const {
    return *ptr_;
}

template<typename T, std::size_t D>
T *Iterator<T, D>::operator->() const {
    return ptr_;
}






