#include <stdexcept>

#include "Index.h"

template<typename T, std::size_t D>
Index<T, D>::Index(Iterable<T, D> *iterable)
        : index_(std::array<std::size_t, D>{}), shape_(iterable->shape()), dims_(iterable->shape().size()) {}

template<typename T, std::size_t D>
std::array<std::size_t, D> Index<T, D>::indices() {
    return index_;
}


template<typename T, std::size_t D>
void Index<T, D>::next() {
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


template<typename T, std::size_t D>
std::string Index<T, D>::toString() {
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