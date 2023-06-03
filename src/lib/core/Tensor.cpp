#include "Tensor.h"

template<typename T, std::size_t D>
template<typename... Dims>
Tensor<T, D>::Tensor(Dims... dims) : shape_{dims...} {
    std::size_t size = 1;
    for (std::size_t i = 0; i < D; ++i) {
        size *= shape_[i];
    }
    data_.resize(size);
}


