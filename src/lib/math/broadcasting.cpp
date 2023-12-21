#pragma once

#include <vector>

#include "Tensor.h"

#define Shape std::vector<std::size_t>

bool isBroadcastableShapes(Shape leftShape, Shape rightShape) {
    int n = std::min(leftShape.size(), rightShape.size());

    int lSize = leftShape.size();
    int rSize = rightShape.size();
    for (int i = 0; i < n; ++i) {
        if (leftShape[lSize - i - 1] != rightShape[rSize - i - 1] && leftShape[lSize - i - 1] != 1 &&
            rightShape[rSize - i - 1] != 1) {
            return false;
        }
    }
    return true;
}

Shape broadcastShapes(Shape leftShape, Shape rightShape) {
    if (!isBroadcastableShapes(leftShape, rightShape)) {
        throw std::invalid_argument("The shapes are incompatible for broadcasting");
    }
    int dims = std::max(leftShape.size(), rightShape.size());
    Shape broadcastResult(dims);

    for (int i = 0; i < dims; ++i) {
        if (leftShape.size() <= i) {
            broadcastResult[i] = rightShape[i];
        } else if (rightShape.size() <= i) {
            broadcastResult[i] = leftShape[i];
        } else {
            broadcastResult[i] = std::max(leftShape[i], rightShape[i]);
        }
    }
    return broadcastResult;
}

template<typename T>
Tensor<T> enhanceImplicitDims(const Tensor<T> &t, const size_t dims) {
    Shape enhancedShape(dims, 1);
    for (int i = 0; i < t.dims(); ++i) {
        enhancedShape[dims - t.dims() + i] = t.shape()[i];
    }
    Tensor<T> enhanced(enhancedShape, t.data());
    return enhanced;
}

template<typename T>
Tensor<T> broadcastOperator(const Tensor<T> &t1, const Tensor<T> &t2, T (*op)(T, T)) {
    Tensor<T> res(broadcastShapes(t1.shape(), t2.shape()));


    Tensor<T> tOrig({1}), tEnhanced({1});
    if (t1.dims() > t2.dims()) {
        tOrig = t1;
        tEnhanced = enhanceImplicitDims(t2, t1.dims());
    } else if (t2.dims() > t1.dims()) {
        tOrig = t2;
        tEnhanced = enhanceImplicitDims(t1, t2.dims());
    }

    Index resIndex = Index::begin(res.shape());
    std::vector<std::size_t> tOrigIndices(res.dims()), tEnhancedIndices(res.dims());

    while (!resIndex.isOut()) {
        tOrigIndices = tEnhancedIndices = resIndex.indices();

        for (int i = 0; i < res.dims(); ++i) {
            if (tOrig.shape()[i] == 1) {
                tOrigIndices[i] = 0;
            } else if (tEnhanced.shape()[i] == 1) {
                tEnhancedIndices[i] = 0;
            }
        }

        res[resIndex] = op(tOrig.at(Index(tOrig.shape(), tOrigIndices)),
                              tEnhanced.at(Index(tEnhanced.shape(), tEnhancedIndices)));
        resIndex.next();
    }

    return res;
}