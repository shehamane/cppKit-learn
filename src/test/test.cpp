#include <iostream>

#include "../lib/core/Tensor.h"
#include "../lib/core/View.h"
#include "../lib/core/iterator/TensorIterator.h"
#include "../lib/core/iterator/ViewIterator.h"


typedef unsigned int ui;

int main() {
    Tensor<int, 2> tensor((ui) 3, (ui) 4);
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 4; j++) {
            tensor[{i, j}] = i * 4 + j;
        }
    }
    TensorIterator<int, 2> tensorIt = TensorIterator<int, 2>(&tensor);
    while (tensorIt <= tensor.end()){
        std::cout << tensorIt.index().toString() << " " << *tensorIt << std::endl;
        ++tensorIt;
    }
    std::cout << "==========================" << std::endl;

    View<int, 2> view(tensor, {0, 1}, {3, 3}, {1, 1});
    ViewIterator<int, 2> viewIt(&view);
    while (viewIt <= view.end()){
        std::cout << viewIt.index().toString() << " " << *viewIt << std::endl;
        ++viewIt;
    }

    return 0;
}
