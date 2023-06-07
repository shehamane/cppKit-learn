#include <stdexcept>
#include <utility>

#include "Index.h"

template<typename T>
Index<T>::Index(Iterable<T> *iterable)
        : shape_(iterable->shape()) {
    index_ = std::vector<size_t>(shape_.size(), 0);
}

template<typename T>
Index<T>::Index(Iterable<T> *iterable, std::vector<std::size_t> indices)
        : index_(std::move(indices)), shape_(iterable->shape()) {}


template<typename T>
std::vector<std::size_t> Index<T>::indices() {
    return index_;
}

template<typename T>
size_t Index<T>::dims() {
    return shape_.size();
}


template<typename T>
void Index<T>::next() {
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


template<typename T>
std::string Index<T>::toString() {
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