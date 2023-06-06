#include "TensorIterator.h"

template<typename T, std::size_t D>
TensorIterator<T, D>::TensorIterator(Iterable<T, D> *iterable)
        : Iterator<T, D>(iterable) {}

template<typename T, std::size_t D>
TensorIterator<T, D> &TensorIterator<T, D>::operator++() {
    ++Iterator<T, D>::ptr_;
    Iterator<T, D>::index_.next();
    return *this;
}

template<typename T, std::size_t D>
const TensorIterator<T, D> TensorIterator<T, D>::operator++(int) {
    TensorIterator<T, D> tmp = *this;
    ++Iterator<T, D>::ptr_;
    Iterator<T, D>::index_.next();
    return tmp;
}