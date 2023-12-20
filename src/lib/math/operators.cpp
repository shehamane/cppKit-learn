#pragma once

#include <math.h>


template<typename T>
T addOp(T x, T y) {
    return x + y;
}

template<typename T>
T subtractOp(T x, T y) {
    return x - y;
}

template<typename T>
T multiplyOp(T x, T y) {
    return x * y;
}

template<typename T>
T divideOp(T x, T y) {
    return x / y;
}

template<typename T>
T restOp(T x, T y) {
    return x % y;
}

template<typename T>
T powOp(T x, T y) {
    return std::pow(x, y);
}

