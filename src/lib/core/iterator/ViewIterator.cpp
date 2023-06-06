#include "ViewIterator.h"

template<typename T, std::size_t D>
ViewIterator<T, D>::ViewIterator(Iterable<T, D> *iterable)
        :Iterator<T, D>(iterable) {}

template<typename T, std::size_t D>
ViewIterator<T, D> &ViewIterator<T, D>::operator++() {
    Iterator<T, D>::index_.next();
    Iterator<T, D>::ptr_ = &Iterator<T, D>::iterable_->operator[](Iterator<T, D>::index());
    return *this;
}
