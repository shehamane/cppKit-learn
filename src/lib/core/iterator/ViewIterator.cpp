#include "ViewIterator.h"

template<typename T>
ViewIterator<T>::ViewIterator(Iterable<T> *iterable)
        :Iterator<T>(iterable) {}

template<typename T>
ViewIterator<T> &ViewIterator<T>::operator++() {
    Iterator<T>::index_.next();
    Iterator<T>::ptr_ = &Iterator<T>::iterable_->operator[](Iterator<T>::index());
    return *this;
}
