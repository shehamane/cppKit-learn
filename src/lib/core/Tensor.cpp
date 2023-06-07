#include "Tensor.h"

#include <utility>

template<typename T>
Tensor<T>::Tensor(std::vector<std::size_t> shape)
        : shape_(std::move(shape)) {
    size_t size = 1;
    for (unsigned long i: shape_) {
        size *= i;
    }
    data_.resize(size);
}

template<typename T>
T &Tensor<T>::operator[](Index<T> index) {
    size_t flatIndex = 0;
    for (size_t i = 0; i < shape_.size(); i++) {
        flatIndex = flatIndex * shape_[i] + index.indices()[i];
    }
    return data_[flatIndex];
}

template<typename T>
T &Tensor<T>::operator[](std::vector<size_t> indices) {
    size_t index = 0;
    for (size_t i = 0; i < shape_.size(); i++) {
        index = index * shape_[i] + indices[i];
    }
    return data_[index];
}


//template<typename T, size_t D>
//Tensor<T, D>& Tensor<T, D>::operator=(const View<T, D>& view) {
//    Tensor<T, D> new_tensor(view.shape());
//    Iterator<T> viewIt = view;
//    Iterator<T> tensorIt = this->start();
//}

template<typename T>
std::vector<size_t> Tensor<T>::shape() {
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
T *Tensor<T>::start() {
    return &(*data_.begin());
}

template<typename T>
T *Tensor<T>::end() {
    return &data_[data().size() - 1];
}
