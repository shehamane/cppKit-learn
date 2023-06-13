#include <iostream>
#include <optional>

#include "../lib/core/Tensor.h"
#include "../lib/core/View.h"

const auto none = std::nullopt;

int main() {
    Tensor<int> tensor({3, 4});
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            tensor[{i, j}] = i * 4 + j;
        }
    }
    // 0 1 2 3
    // 4 5 6 7
    // 8 9 10 11
    Tensor<int> tensor1 = tensor[2];
    int x = tensor[0][3];
    int y = tensor1[2];

    std:: cout << x + y << std::endl;

    View<int> slice = tensor[{{0, 3, 2}, {0, 2, 1}}];
    for (int elem: slice){
        std::cout << elem << " ";
    }

    return 0;
}
