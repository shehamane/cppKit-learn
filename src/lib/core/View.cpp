#include "View.h"


template<typename T, size_t D>
View<T, D>::View(Tensor<T, D> &tensor, std::array<size_t, D> start, std::array<size_t, D> end,
                 std::array<size_t, D> step) :
        tensor_(tensor), start_(start), end_(end), step_(step) {
    for (size_t i = 0; i < shape_.size(); i++) {
        shape_[i] = (end_[i] - start_[i] + step_[i] - 1) / step_[i];
    }
}

template<typename T, size_t D>
T &View<T, D>::operator[](std::array<size_t, D> indices) {
    std::array<size_t, D> new_indices;
    for (size_t i = 0; i < indices.size(); i++) {
        new_indices[i] = start_[i] + indices[i] * step_[i];
    }
    return tensor_[new_indices];
}

template<typename T, size_t D>
std::array<size_t, D> View<T, D>::shape() const {
    return shape_;
}
