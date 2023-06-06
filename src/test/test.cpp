#include <iostream>

#include "../lib/core/Tensor.h"
#include "../lib/core/View.h"
#include "../lib/core/iterator/TensorIterator.h"


typedef unsigned int ui;

int main() {
    Tensor<int, 2> t((ui) 3, (ui) 4);
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 4; j++) {
            t[{i, j}] = i * 4 + j;
        }
    }
    TensorIterator<int, 2> tensorIt = TensorIterator<int, 2>(&t);
    while (tensorIt != t.end()){
        std::cout << tensorIt.index().toString() << " " << *tensorIt << std::endl;
        ++tensorIt;
    }

    return 0;
}
