#ifndef CPPKIT_LEARN_TENSOR_H
#define CPPKIT_LEARN_TENSOR_H

#include <vector>
#include <array>
#include <iostream>

template<typename T, size_t D>
class Tensor {
private:
    std::array<size_t, D> shape_;
    std::array<size_t, D> strides_{1};
    std::vector<T> data_;
public:
    template<typename... Dims>
    explicit Tensor(Dims... dims);

    T &operator[](std::array<size_t, D> indices) {
        size_t index = 0;
        for (size_t i = 0; i < shape_.size(); i++) {
            index = index * shape_[i] + indices[i];
        }
        return data_[index];
    }

    std::array<size_t, D> shape() const {
        return shape_;
    }
};


#include "Tensor.cpp"

#endif //CPPKIT_LEARN_TENSOR_H
