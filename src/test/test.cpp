#include <iostream>

#include "../lib/core/Tensor.h"
#include "../lib/core/View.h"
#include "../lib/core/iterator/TensorIterator.h"
#include "../lib/core/iterator/ViewIterator.h"


typedef unsigned int ui;

int main() {
    Tensor<int> tensor({3, 4});
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            tensor[{(ui)i, (ui)j}] = i *  4 + j;
        }
    }
    TensorIterator<int> tensorIt = TensorIterator<int>(&tensor);
    while (tensorIt <= tensor.end()) {
        std::cout << tensorIt.index().toString() << " " << *tensorIt << std::endl;
        ++tensorIt;
    }
    std::cout << "==========================" << std::endl;

    View<int> view(tensor, {{0, 3, 1}, {1, 3, 1}});
    ViewIterator<int> viewIt(&view);
    while (viewIt <= view.end()) {
        std::cout << viewIt.index().toString() << " " << *viewIt << std::endl;
        ++viewIt;
    }

    return 0;
}
