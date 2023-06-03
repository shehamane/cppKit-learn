#ifndef CPPKIT_LEARN_VIEW_H
#define CPPKIT_LEARN_VIEW_H

#include <array>
#include <vector>

#include "Tensor.h"

template<typename T, size_t D>
class View {
private:
    Tensor<T, D> &tensor_;
    std::array<size_t, D> start_;
    std::array<size_t, D> end_;
    std::array<size_t, D> step_;
    std::array<size_t, D> shape_;
public:
    View(Tensor<T, D> &tensor, std::array<size_t, D> start, std::array<size_t, D> end, std::array<size_t, D> step);

    T &operator[](std::array<size_t, D> indices);

    std::vector<size_t> shape() const;

};


#include "View.cpp"

#endif //CPPKIT_LEARN_VIEW_H
