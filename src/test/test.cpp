#include "../lib/core/Tensor.h"
#include "../lib/core/View.h"


typedef unsigned int ui;

int main() {
    Tensor<int, 2> t((ui) 3, (ui) 4);
    // fill the tensor with values
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 4; j++) {
            t[{i, j}] = i * 4 + j;
        }
    }
    // create a view of the tensor along columns
    View<int, 2> view(t, {0, 1}, {3, 3}, {1, 1});
    // modify the view
    return 0;
}
