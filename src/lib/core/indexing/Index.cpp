#include <stdexcept>
#include <utility>

#include "Index.h"

Index::Index(std::vector<size_t> shape) : shape_(std::move(shape)) {
    indices_ = std::vector<size_t>(shape.size(), 0);
}

Index::Index(std::vector<size_t> shape, std::vector<std::size_t> indices)
        : indices_(std::move(indices)), shape_(std::move(shape)) {
    if (indices.size() != shape.size()) {
        throw std::invalid_argument("indices and shape don't match each other");
    }
}

Index::Index(std::vector<size_t> shape, std::initializer_list<int> indicesList)
        : shape_(shape) {
    if (indicesList.size() != shape.size()) {
        throw std::invalid_argument("indices and shape don't match each other");
    }
    std::vector<int> indices(indicesList);
    indices_.resize(indices.size());
    for (int i = 0; i < indices.size(); ++i) {
        if (indices[i] < 0) {
            if (indices[i] + static_cast<int>(shape[i]) < 0) {
                throw std::out_of_range("negative index out of range");
            }
            indices_[i] = shape[i] + indices[i];
        } else {
            if (indices[i] >= shape[i]) {
                throw std::out_of_range("index out of range");
            }
            indices_[i] = indices[i];
        }
    }
}

//Index::Index(std::vector<size_t> shape, unsigned int index)
//        : shape_(std::move(shape)) {
//    std::vector<size_t> indices(shape.size());
//    for (int i = 0; i < shape.size(); ++i) {
//        indices[i] = index / shape[i];
//
//        index = index % shape[i];
//    }
//}

std::vector<std::size_t> Index::indices() {
    return indices_;
}

size_t Index::dims() {
    return shape_.size();
}


void Index::next() {
    indices_[dims() - 1] += 1;
    for (int dim = static_cast<int>(dims()) - 1; dim >= 0; --dim) {
        if (indices_[dim] == shape_[dim]) {
            if (dim == 0) {
                indices_ = shape_;
                break;
            } else {
                indices_[dim] = 0;
                indices_[dim - 1] += 1;
            }
        }
    }
}

bool Index::isOut() {
    for (int i = 0; i < dims(); ++i) {
        if (indices_[i] >= shape_[i]) {
            return true;
        }
    }
    return false;
}

size_t Index::toFlat() {
    size_t flat = 0;
    size_t stride = 1;
    for (int i = shape_.size() - 1; i >= 0; --i) {
        flat += indices_[i] * stride;
        stride *= shape_[i];
    }
    return flat;
}

std::string Index::toString() {
    std::string s = "(";
    for (int i = 0; i < indices_.size(); ++i) {
        s += std::to_string(indices_[i]);
        if (i != indices_.size() - 1) {
            s += ", ";
        }
    }
    s += ")";
    return s;
}

bool Index::operator==(const Index &other) const {
    return indices_ == other.indices_;
}

bool Index::operator!=(const Index &other) const {
    return indices_ != other.indices_;
}

Index Index::begin(const std::vector<size_t> &shape) {
    return Index(shape, std::vector<size_t>(shape.size(), 0));
}

Index Index::end(const std::vector<size_t> &shape) {
    return Index(shape, shape);
}

size_t &Index::operator[](int i) {
    return indices_[i];
}