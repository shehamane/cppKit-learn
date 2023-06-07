#include <stdexcept>

#include "Index.h"

template<typename T>
Index<T>::Index(Iterable<T> *iterable)
        : shape_(iterable->shape()), dims_(iterable->shape().size()) {
    index_ = std::vector<size_t>(dims_, 0);
}

template<typename T>
Index<T>::Index(Iterable<T> *iterable, std::vector<std::size_t> indices)
        : index_(indices), shape_(iterable->shape()), dims_{indices.size()} {}


template<typename T>
std::vector<std::size_t> Index<T>::indices() {
    return index_;
}


template<typename T>
void Index<T>::next() {
    index_[dims_ - 1] += 1;
    for (int dim = dims_ - 1; dim >= 0; --dim) {
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