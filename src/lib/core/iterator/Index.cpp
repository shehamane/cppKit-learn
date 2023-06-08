#include <stdexcept>
#include <utility>

#include "Index.h"

Index::Index(std::vector<size_t> shape, std::vector<std::size_t> indices)
        : index_(std::move(indices)), shape_(std::move(shape)) {}


std::vector<std::size_t> Index::indices() {
    return index_;
}

size_t Index::dims() {
    return shape_.size();
}


void Index::next() {
    index_[dims() - 1] += 1;
    for (int dim = dims() - 1; dim >= 0; --dim) {
        if (index_[dim] == shape_[dim]) {
            if (dim == 0) {
                break;
            } else {
                index_[dim] = 0;
                index_[dim - 1] += 1;
            }
        }
    }
}


std::string Index::toString() {
    std::string s = "(";
    for (int i = 0; i < index_.size(); ++i) {
        s += std::to_string(index_[i]);
        if (i != index_.size() - 1) {
            s += ", ";
        }
    }
    s += ")";
    return s;
}

bool Index::operator==(const Index &other) const {
    return index_ == other.index_;
}

bool Index::operator!=(const Index &other) const {
    return index_ != other.index_;
}

Index Index::begin(const std::vector<size_t>& shape) {
    return Index(shape, std::vector<size_t>(shape.size(), 0));
}

Index Index::end(const std::vector<size_t>& shape) {
    return Index(shape, shape);
}
