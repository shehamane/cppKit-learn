#include "TensorIterator.h"

template<typename T>
TensorIterator<T>::TensorIterator(Iterable<T> *iterable)
        : Iterator<T>(iterable) {}

template<typename T>
TensorIterator<T> &TensorIterator<T>::operator++() {
    ++Iterator<T>::ptr_;
    Iterator<T>::index_.next();
    return *this;
}
