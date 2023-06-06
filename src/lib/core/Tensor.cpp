#include "Tensor.h"

template<typename T, size_t D>
template<typename... Dims>
Tensor<T, D>::Tensor(Dims... dims) : shape_{dims...} {
    size_t size = 1;
    for (size_t i = 0; i < D; ++i) {
        size *= shape_[i];
    }
    data_.resize(size);
}

template<typename T, size_t D>
T &Tensor<T, D>::operator[](std::array<size_t, D> indices) {
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

template<typename T, size_t D>
std::array<size_t, D> Tensor<T, D>::shape() {
    return shape_;
}

template<typename T, size_t D>
size_t Tensor<T, D>::dims() const {
    return D;
}

template<typename T, size_t D>
std::vector<T> Tensor<T, D>::data() const {
    return data_;
}

template<typename T, size_t D>
T *Tensor<T, D>::start() {
    return &(*data_.begin());
}

template<typename T, size_t D>
T *Tensor<T, D>::end() {
    return &(*data_.end());
}
