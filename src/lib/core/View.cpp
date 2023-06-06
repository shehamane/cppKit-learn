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
T &View<T, D>::operator[](Index<T, D> index) {
    std::array<size_t, D> new_indices;
    for (size_t i = 0; i < index.indices().size(); i++) {
        new_indices[i] = start_[i] + index.indices()[i] * step_[i];
    }
    return tensor_[new_indices];
}

template<typename T, size_t D>
std::array<size_t, D> View<T, D>::shape() {
    return shape_;
}

template<typename T, size_t D>
T *View<T, D>::start() {
    auto startIndices = start_;
    return &(tensor_[startIndices]);
}

template<typename T, size_t D>
T *View<T, D>::end() {
    auto endIndices = shape_;
    for (int i = 0; i < D; ++i){
        endIndices[i] -= 1;
    }
    auto endIndex = Index<T, D>(&tensor_, endIndices);
    endIndex.next();
    return &(tensor_[endIndex]);
}

