#include "View.h"

template<typename T>
View<T>::View(Tensor<T> &tensor, const std::vector<std::array<size_t, 3>>& slices)
        : tensor_(tensor) {
    for (auto slice: slices) {
        starts_.push_back(slice[0]);
        ends_.push_back(slice[1]);
        steps_.push_back(slice[2]);
        shape_.push_back(
                (slice[1] - slice[0] + slice[2] - 1) / slice[2]
        );
    }
}

template<typename T>
T &View<T>::operator[](Index index) {
    std::vector<size_t> new_indices(index.indices().size());
    for (size_t i = 0; i < index.indices().size(); i++) {
        new_indices[i] = starts_[i] + index.indices()[i] * steps_[i];
    }
    return tensor_[new_indices];
}

template<typename T>
std::vector<size_t> View<T>::shape() {
    return shape_;
}

template<typename T>
size_t View<T>::dims() {
    return tensor_.dims();
}

template<typename T>
T *View<T>::begin() {
    auto startIndices = starts_;
    return &(tensor_[startIndices]);
}

template<typename T>
T *View<T>::end() {
    auto endIndices = shape_;
    for (int i = 0; i < dims(); ++i) {
        endIndices[i] -= 1;
    }
    auto endIndex = Index(tensor_.shape(), endIndices);
    endIndex.next();
    return &(tensor_[endIndex]);
}

