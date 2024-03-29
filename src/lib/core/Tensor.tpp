#include "Tensor.h"

#include "operations.cpp"

#include <cmath>

//***********************************************************
// Constructors
template<typename T>
Tensor<T>::Tensor(std::vector<std::size_t> shape)
        : shape_(std::move(shape)) {
    if (shape_.empty()) {
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
Tensor<T>::Tensor(std::vector<std::size_t> shape, std::vector<T> data)
        : Tensor(shape) {
    data_ = data;
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
Tensor<T>::Tensor(const Tensor<T> &other) {
    shape_ = other.shape_;
    data_ = other.data_;
}


//***********************************************************
// Indexing
template<typename T>
T &Tensor<T>::operator[](Index index) {
    if (index.isOut()) {
        throw std::out_of_range("index out of range");
    }
    return data_[index.toFlat()];
}

template<typename T>
T &Tensor<T>::operator[](const std::initializer_list<int> &indices) {
    return (*this).operator[](Index(shape_, indices));
}


template<typename T>
T Tensor<T>::at(Index index) const {
    if (index.isOut()) {
        throw std::out_of_range("index out of range");
    }
    return data_[index.toFlat()];
}


//***********************************************************
// Slicing
template<typename T>
View<T> Tensor<T>::slice(const std::vector<Range> ranges) {
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
        if (begin >= shape_[i] || begin < (int) -shape_[i] || end > shape_[i] || end < (int) -shape_[i]) {
            throw std::out_of_range("invalid range index");
        }
        normalRanges[i][0] = begin;
        normalRanges[i][1] = end;
        normalRanges[i][2] = step;
    }
    for (int i = ranges.size(); i < dims(); ++i) {
        normalRanges[i][0] = 0;
        normalRanges[i][1] = shape_[i];
        normalRanges[i][2] = 1;
    }
    return View<T>(*this, normalRanges);
}

template<typename T>
View<T> Tensor<T>::operator[](int index) {
    if (index >= shape_[0] || index < (int) -shape_[0]) {
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


//***********************************************************
// Getters
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


//***********************************************************
// Unary operations
template<typename T>
Tensor<T> Tensor<T>::transpose() {
    return transposeOperation(*this);
}

template<typename T>
Tensor<T> Tensor<T>::reshape(std::vector<size_t> newShape) {
    return reshapeOperation(*this, newShape);
}


//***********************************************************
// Binary operations
template<typename T>
Tensor<T> Tensor<T>::operator+(const Tensor<T> &other) const {
    return add(*this, other);
}

template<typename T>
Tensor<T> Tensor<T>::operator-(const Tensor<T> &other) const {
    return subtract(*this, other);
}

template<typename T>
Tensor<T> Tensor<T>::operator*(const Tensor<T> &other) const {
    return multiply(*this, other);
}

template<typename T>
Tensor<T> Tensor<T>::operator/(const Tensor<T> &other) const {
    return divide(*this, other);
}

template<typename T>
Tensor<T> Tensor<T>::operator%(const Tensor<T> &other) const {
    return rest(*this, other);
}

template<typename T>
Tensor<T> Tensor<T>::pow(const Tensor<T> &other) const {
    return power(*this, other);
}

template<typename T>
Tensor<T> Tensor<T>::matmul(const Tensor<T> &other) const {
    return matmulOperation(*this, other);
}

//***********************************************************
// Binary operations with numbers
template<typename T>
template<
        typename V,
        typename
>
Tensor<T> Tensor<T>::operator+(const V &other) const {
    return *this + Tensor<T>({1}, {other});
}

template<typename T>
template<
        typename V,
        typename
>
Tensor<T> Tensor<T>::operator-(const V &other) const {
    return *this - Tensor<T>({1}, {other});
}

template<typename T>
template<
        typename V,
        typename
>
Tensor<T> Tensor<T>::operator*(const V &other) const {
    return *this * Tensor<T>({1}, {other});
}

template<typename T>
template<
        typename V,
        typename
>
Tensor<T> Tensor<T>::operator/(const V &other) const {
    return *this + Tensor<T>({1}, {other});
}

template<typename T>
template<
        typename V,
        typename
>
Tensor<T> Tensor<T>::operator%(const V &other) const {
    return *this % Tensor<T>({1}, {other});
}

template<typename T>
template<
        typename V,
        typename
>
Tensor<T> Tensor<T>::pow(const V &other) const {
    return this->pow(Tensor<T>({1}, {other}));
}


//***********************************************************
// Static initializers

template<typename T>
Tensor<T> Tensor<T>::full(std::vector<size_t> shape, T val) {
    Tensor<T> tensor(shape);
    for (T &e: tensor) {
        e = val;
    }
    return tensor;
}

template<typename T>
template<typename V, typename>
Tensor<T> Tensor<T>::zeros(Shape shape) {
    return Tensor<T>::full(shape, 0);
}


template<typename T>
template<typename V, typename>
Tensor<T> Tensor<T>::ones(Shape shape) {
    return Tensor<T>::full(shape, 1);
}

template<typename T>
template<typename V, typename>
Tensor<T> Tensor<T>::range(T start, T end, T step) {
    size_t size = std::ceil((float) (end - start) / step);
    Tensor<T> tensor({size});

    T curr = start;
    for (T &e: tensor) {
        e = curr;
        curr += step;
    }
    return tensor;
}
