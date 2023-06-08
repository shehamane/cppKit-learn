#include "Tensor.h"

#include <utility>
#include <memory>

template<typename T>
Tensor<T>::Tensor(std::vector<std::size_t> shape)
        : shape_(std::move(shape)) {
    data_.resize(size());
}


template<typename T>
Tensor<T>::Tensor(const View<T> &view)
: shape_(view.shape()){
    data_.resize(size());
}

template<typename T>
T &Tensor<T>::operator[](Index index) {
    if (index.isOut()){
        throw std::out_of_range("Index out of range");
    }
    size_t flatIndex = 0;
    for (size_t i = 0; i < shape_.size(); i++) {
        flatIndex = flatIndex * shape_[i] + index.indices()[i];
    }
    return data_[flatIndex];
}

template<typename T>
T &Tensor<T>::operator[](const std::vector<int>& indices) {
    return (*this)[Index(shape_, indices)];
}

template<typename T>
std::vector<size_t> Tensor<T>::shape() const {
    return shape_;
}

template<typename T>
size_t Tensor<T>::dims() const {
    return shape_.size();
}

template<typename T>
std::vector<T> Tensor<T>::data() const {
    return data_;
}

template<typename T>
size_t Tensor<T>::size() const {
    size_t size = 1;
    for (unsigned long i: shape_) {
        size *= i;
    }
    return size;
}


template<typename T>
Iterator<T> Tensor<T>::begin() {
    return Iterator<T>(this, Index::begin(shape_));
}

template<typename T>
Iterator<T> Tensor<T>::end() {
    return Iterator<T>(this, Index::end(shape_));
}
