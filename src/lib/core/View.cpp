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
std::vector<size_t> View<T>::shape() const {
    return shape_;
}

template<typename T>
size_t View<T>::dims() const {
    return tensor_.dims();
}

template<typename T>
Iterator<T> View<T>::begin() {
    return Iterator<T>(this, Index::begin(shape_));
}

template<typename T>
Iterator<T> View<T>::end() {
    return Iterator<T>(this, Index::end(shape_))
}

