#pragma once

#include "Tensor.h"
#include "broadcasting.cpp"
#include "operators.cpp"

#define Shape std::vector<size_t>


template<typename T>
Tensor<T> add(const Tensor<T> &t1, const Tensor<T> &t2) {
    return broadcastOperator(t1, t2, addOp);
}

template<typename T>
Tensor<T> subtract(const Tensor<T> &t1, const Tensor<T> &t2) {
    return broadcastOperator(t1, t2, subtractOp);
};

template<typename T>
Tensor<T> multiply(const Tensor<T> &t1, const Tensor<T> &t2) {
    return broadcastOperator(t1, t2, multiplyOp<T>);
};

template<typename T>
Tensor<T> divide(const Tensor<T> &t1, const Tensor<T> &t2) {
    return broadcastOperator(t1, t2, divideOp);
};

template<typename T>
Tensor<T> rest(const Tensor<T> &t1, const Tensor<T> &t2) {
    return broadcastOperator(t1, t2, restOp);
};

template<typename T>
Tensor<T> power(const Tensor<T> &t1, const Tensor<T> &t2) {
    return broadcastOperator(t1, t2, powOp);
};


std::vector<size_t> permute(std::vector<size_t> a, std::vector<size_t> permutation) {
    std::vector<size_t> res(a.size());

    for (int i = 0; i < a.size(); ++i) {
        res[i] = a[permutation[i]];
    }
    return res;
}


template<typename T>
Tensor<T> transposeOperation(const Tensor<T> &t, std::vector<size_t> permutation = {}) {
    if (t.dims() == 1) {
        return Tensor<T>(t);
    } else {
        if (permutation.size() == 0) {
            permutation.resize(t.shape().size());
            for (int i = 0; i < t.dims() - 1; ++i) {
                permutation[i] = i + 1;
            }
            permutation[t.dims() - 1] = t.dims() - 2;
        } else if (permutation.size() != t.dims()) {
            throw std::invalid_argument("Permutation cannot be applied to Tensor shape");
        }

        Tensor<T> res(permute(t.shape(), permutation));

        Index tIndex = Index::begin(t.shape());
        Index transposedIndex = Index::begin(t.shape());

        while (!tIndex.isOut()) {
            transposedIndex = Index(t.shape(), permute(tIndex.indices(), permutation));
            res[transposedIndex] = t.at(tIndex);
            tIndex.next();
        }
        return res;
    }
}

template<typename T>
Tensor<T> reshapeOperation(const Tensor<T> &t, Shape newShape) {
    size_t newSize = 1;
    for (int i = 0; i < newShape.size(); ++i) {
        newSize *= newShape[i];
    }
    if (t.size() != newSize) {
        throw std::invalid_argument("New shape is not compatible with original array");
    }
    return Tensor<T>(newShape, t.data());
}


template<typename T>
Tensor<T> matmulOperation(const Tensor<T> &lTensor, const Tensor<T> &rTensor) {
    if (lTensor.dims() > 2 || rTensor.dims() > 2) {
        throw std::invalid_argument("The tensors are not matrices or vectors");
    }
    Tensor<T> lt = lTensor, rt = rTensor;
    if (lt.dims() == 1) {
        lt.reshape({1, lt.size()});
    }
    if (rt.dims() == 1) {
        rt.reshape({1, rt.size()});
    }
    size_t l = lt.shape()[lt.dims() - 2], n = rt.shape()[rt.dims() - 1];
    if (lt.shape()[lt.dims() - 1] != rt.shape()[rt.dims() - 2]) {
        throw std::invalid_argument("The dimensions of tensors are not suitable for multiplication");
    }
    size_t m = lt.shape()[lt.dims() - 1];

    Tensor<T> res({m, m});

    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < n; ++j) {
            res[{i, j}] = 0;
            for (int k = 0; k < m; ++k) {
                res[{i, j}] += lt[{i, k}] * rt[{k, j}];
            }
        }
    }
    return res;
}