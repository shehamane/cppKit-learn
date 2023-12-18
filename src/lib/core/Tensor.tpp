#include "Tensor.h"

template<typename T>
Tensor<T>::Tensor(std::vector<std::size_t> shape)
        : shape_(std::move(shape)) {
    if (shape_.empty()){
        throw std::invalid_argument("Invalid dimension");
    }
    for (size_t dimSize: shape_) {
        if (dimSize <= 0) {
            throw std::invalid_argument("Invalid dimension size");
        }
    }
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
T &Tensor<T>::at(Index index) {
    if (index.isOut()) {
        throw std::out_of_range("index out of range");
    }
    return data_[index.toFlat()];
}

template<typename T>
T &Tensor<T>::operator[](const std::initializer_list<int> &indices) {
    return (*this).at(Index(shape_, indices));
}


template<typename T>
View<T> Tensor<T>::slice(const std::vector<std::array<size_t, 3>> &ranges) {
    if (ranges.size() != dims()) {
        throw std::invalid_argument("ranges dimension is not equal to the original tensor dimension");
    }
    return View<T>(*this, ranges);
}

template<typename T>
View<T> Tensor<T>::operator[](const std::vector<Range> ranges) {
    if (ranges.size() > dims()) {
        throw std::invalid_argument("ranges dimension is greater then the original tensor dimension");
    }
    std::vector<std::array<size_t, 3>> normalRanges(dims());
    for (int i = 0; i < ranges.size(); ++i) {
        auto [begin, end, step] = ranges[i].decompose();
        if (begin < 0) {
            begin = shape_[i] - begin;
        }
        if (end <= 0) {
            end = shape_[i] - end;
        }
        if (begin >= shape_[i] || begin < (int)-shape_[i] || end > shape_[i] || end < (int)-shape_[i]) {
            throw std::out_of_range("invalid range index");
        }
        normalRanges[i][0] = begin;
        normalRanges[i][1] = end;
        normalRanges[i][2] = step;
    }
    for (int i = ranges.size(); i < dims(); ++i){
        normalRanges[i][0] = 0;
        normalRanges[i][1] = shape_[i];
        normalRanges[i][2] = 1;
    }
    return this->slice(normalRanges);
}

template<typename T>
View<T> Tensor<T>::operator[](int index) {
    if (index >= shape_[0] || index < (int) -shape_[0]){
        throw std::out_of_range("index out of range");
    }

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
