#include <iostream>
#include <optional>

#include "../lib/core/Tensor.h"
#include "../lib/core/View.h"

// 0 1 2 3
// 4 5 6 7
// 8 9 10 11


typedef unsigned int ui;

int main() {
    Tensor<int> tensor({3, 4});
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            tensor[{i, j}] = i * 4 + j;
        }
    }
    auto view = tensor[2];
    Tensor<int> tensor1 = view;

    std:: cout << tensor1[3];

    return 0;
}
