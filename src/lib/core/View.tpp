#include "View.h"

template<typename T>
View<T>::View(Tensor<T> &tensor, const std::vector<std::array<size_t, 3>> &slices, size_t currDim)
        : tensor_(tensor), currDim_(currDim) {
    if (slices.size() != tensor.dims()) {
        throw std::invalid_argument("ranges dimension is not equal to the original tensor dimension");
    }
    for (int i = 0; i < tensor.dims(); ++i) {
        auto slice = slices[i];
        if (slice[0] >= tensor.shape()[i] || slice[1] > tensor.shape()[i]) {
            throw std::out_of_range("range index out of range");
        }
        if (slice[2] == 0) {
            throw std::invalid_argument("zero step in range");
        }
    }
    for (auto slice: slices) {
        starts_.push_back(slice[0]);
        ends_.push_back(slice[1]);
        steps_.push_back(slice[2]);
        shape_.push_back(
                (slice[1] - slice[0] + slice[2] - 1) / slice[2]
        );
    }
    actualShape_ = std::vector<size_t>(shape_.begin() + currDim, shape_.end());
}

template<typename T>
View<T> View<T>::operator[](int index) {
    if (isOneElement()) {
        throw std::exception();
    }
    size_t normalIndex;
    if (index < 0) {
        normalIndex = shape_[0] + index;
    } else {
        normalIndex = index;
    }
    std::vector<std::array<size_t, 3>> slices;
    for (int i = 0; i < dims(); ++i) {
        if (i == currDim_) {
            slices.push_back({normalIndex, normalIndex + 1, 1});
        } else {
            slices.push_back({starts_[i], ends_[i], steps_[i]});
        }
    }
    return View<T>(tensor_, slices, currDim_ + 1);
}

template<typename T>
View<T>::operator T&() const {
    if (!isOneElement()) {
        throw std::out_of_range("attempt to cast a non-1-element representation to an element type");
    }
    return tensor_[Index(tensor_.shape(), starts_)];
}

template<typename T>
T &View<T>::operator[](Index index) {
    if (index.dims() != actualDims()) {
        throw std::invalid_argument("Invalid index dimension");
    }
    std::vector<size_t> new_indices(dims());
    for (size_t i = 0; i < currDim_; ++i) {
        new_indices[i] = starts_[i];
    }
    for (size_t i = currDim_; i < dims(); ++i) {
        new_indices[i] = starts_[i] + index.indices()[i - currDim_] * steps_[i];
    }

    return tensor_[(Index(tensor_.shape(), new_indices))];
}

template<typename T>
T &View<T>::operator[](const std::initializer_list<int> &indices) {
    return (*this)[(Index(actualShape_, indices))];
}

template<typename T>
T View<T>::at(Index index) const {
    if (index.dims() != actualDims()) {
        throw std::invalid_argument("Invalid index dimension");
    }
    std::vector<size_t> new_indices(dims());
    for (size_t i = 0; i < currDim_; ++i) {
        new_indices[i] = starts_[i];
    }
    for (size_t i = currDim_; i < dims(); ++i) {
        new_indices[i] = starts_[i] + index.indices()[i - currDim_] * steps_[i];
    }

    return tensor_[(Index(tensor_.shape(), new_indices))];
}


template<typename T>
bool View<T>::isOneElement() const {
    for (int i = 0; i < dims(); ++i) {
        if (shape_[i] > 1) {
            return false;
        }
    }
    return true;
}

template<typename T>
std::vector<size_t> View<T>::actualShape() const {
    return actualShape_;
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
size_t View<T>::actualDims() const {
    return actualShape_.size();
}

template<typename T>
size_t View<T>::currDim() const {
    return currDim_;
}

template<typename T>
Iterator<T> View<T>::begin() const {
    return Iterator<T>(const_cast<View<T> *>(this), Index::begin(actualShape_));
}

template<typename T>
Iterator<T> View<T>::end() const {
    return Iterator<T>(const_cast<View<T> *>(this), Index::begin(actualShape_));
}

template<typename T>
Iterator<T> View<T>::begin() {
    return Iterator<T>(this, Index::begin(actualShape_));
}

template<typename T>
Iterator<T> View<T>::end() {
    return Iterator<T>(this, Index::end(actualShape_));
}

