#include "Tensor.h"

#include <utility>
#include <memory>

template<typename T>
Tensor<T>::Tensor(std::vector<std::size_t> shape)
        : shape_(std::move(shape)) {
    data_.resize(size());
}


template<typename T>
Tensor<T>::Tensor(View<T> &view) {
    for (int i = view.currDim(); i < view.dims(); ++i) {
        shape_.push_back(view.shape()[i]);
    }
    data_.resize(size());
    auto tensorIt = begin();
    auto viewIt = view.begin();

    while (tensorIt != end()) {
        *tensorIt = *viewIt;
        ++tensorIt;
        ++viewIt;
    }
}

template<typename T>
Tensor<T>::Tensor(const View<T> &view) {
    for (int i = view.currDim(); i < view.dims(); ++i) {
        shape_.push_back(view.shape()[i]);
    }
    data_.resize(size());
    auto tensorIt = begin();
    auto viewIt = view.begin();

    while (tensorIt != end()) {
        *tensorIt = *viewIt;
        ++tensorIt;
        ++viewIt;
    }
}

template<typename T>
T &Tensor<T>::operator[](Index index) {
    if (index.isOut()) {
        throw std::out_of_range("Index out of range");
    }
    size_t flatIndex = 0;
    for (size_t i = 0; i < shape_.size(); i++) {
        flatIndex = flatIndex * shape_[i] + index.indices()[i];
    }
    return data_[flatIndex];
}

template<typename T>
T &Tensor<T>::operator[](const std::vector<int> &indices) {
    return (*this)[Index(shape_, indices)];
}


template<typename T>
View<T> Tensor<T>::operator[](int index) {
    size_t normalIndex;
    if (index < 0) {
        normalIndex = shape_[0] + index;
    } else {
        normalIndex = index;
    }
    std::vector<std::array<size_t, 3>> slices = {{normalIndex, normalIndex + 1, 1}};
    for (int i = 1; i < dims(); ++i) {
        slices.push_back({0, shape_[i], 1});
    }
    return View<T>(*this, slices, 1);
}


template<typename T>
View<T> Tensor<T>::slice(const std::vector<std::array<size_t, 3>> &slices) {
    if (slices.size() != dims()) {
        throw std::out_of_range("Invalid slice dimension");
    }
    return View<T>(*this, slices);
}

template<typename T>
View<T> Tensor<T>::operator[](const std::vector<std::array<std::optional<int>, 3>> &slices) {
    if (slices.size() > dims()) {
        throw std::out_of_range("Invalid slice dimensions");
    }
    std::vector<std::array<size_t, 3>> normalSlices(slices.size());
    for (int i = 0; i < slices.size(); ++i) {
        if (!slices[i][0].has_value()) {
            normalSlices[i][0] = 0;
        } else {
            if (slices[i][0].value() < 0 || slices[i][0].value() >= shape_[i]) {
                throw std::out_of_range("Invalid slice begin index for dimension " + std::to_string(i));
            }
            normalSlices[i][0] = slices[i][0].value();
        }
        if (!slices[i][1].has_value()) {
            normalSlices[i][1] = shape_[i];
        } else {
            if (slices[i][1].value() >= shape_[i] ||
                (slices[i][1].value() < 0 && slices[i][1].value() + shape_[i] < 0)) {
                throw std::out_of_range("Invalid slice end index for dimension " + std::to_string(i));
            }
            if (slices[i][1].value() < 0) {
                normalSlices[i][1] = shape_[i] + slices[i][1].value();
            } else {
                normalSlices[i][1] = slices[i][1].value();
            }
        }
        if (!slices[i][2].has_value()) {
            normalSlices[i][2] = 1;
        } else {
            if (slices[i][2].value() <= 0) {
                throw std::out_of_range("Negative slice step");
            }
            normalSlices[i][2] = slices[i][2].value();
        }
    }
    return this->slice(normalSlices);
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
Iterator<T> Tensor<T>::begin() const {
    return Iterator<T>(const_cast<Tensor<T> *>(this), Index::begin(shape_));
}

template<typename T>
Iterator<T> Tensor<T>::end() const {
    return Iterator<T>(const_cast<Tensor<T> *>(this), Index::begin(shape_));
}

template<typename T>
Iterator<T> Tensor<T>::begin() {
    return Iterator<T>(this, Index::begin(shape_));
}

template<typename T>
Iterator<T> Tensor<T>::end() {
    return Iterator<T>(this, Index::end(shape_));
}
