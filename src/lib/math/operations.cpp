#pragma once

#include "Tensor.h"
#include "broadcasting.cpp"
#include "operators.cpp"


template<typename T>
Tensor<T> add(Tensor<T> &t1, Tensor<T> &t2) {
    return broadcastOperator(t1, t2, addOp);
}

template<typename T>
Tensor<T> subtract(Tensor<T> &t1, Tensor<T> &t2) {
    return broadcastOperator(t1, t2, subtractOp);
};

template<typename T>
Tensor<T> multiply(const Tensor<T> &t1, const Tensor<T> &t2) {
    return broadcastOperator(t1, t2, multiplyOp<T>);
};

template<typename T>
Tensor<T> divide(Tensor<T> &t1, Tensor<T> &t2) {
    return broadcastOperator(t1, t2, divideOp);
};

template<typename T>
Tensor<T> rest(Tensor<T> &t1, Tensor<T> &t2) {
    return broadcastOperator(t1, t2, restOp);
};

template<typename T>
Tensor<T> pow(Tensor<T> &t1, Tensor<T> &t2) {
    return broadcastOperator(t1, t2, powOp);
};
