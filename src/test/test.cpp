#include <iostream>

#include "../lib/core/Tensor.h"


typedef unsigned int ui;

int main() {
    Tensor<int> tensor({3, 4});
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            tensor[{i, j}] = i * 4 + j;
        }
    }
    for (auto x: tensor) {
        std::cout << x;
    }

    return 0;
}
