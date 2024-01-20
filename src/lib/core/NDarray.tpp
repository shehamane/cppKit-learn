#include "NDArray.h"

#include "vector"

#define Shape std::vector<size_t>

template<typename T>
std::ostream &operator<<(std::ostream &os, const NDArray<T> &tensor) {
    Shape shape = tensor.shape();
    size_t dims = shape.size();
    if (dims == 1) {
        os << "[ ";
        for (size_t i = 0; i < shape[0]; ++i) {
            os << tensor.data()[i] << " ";
        }
        os << "]";
        return os;
    } else if (dims == 2) {
        os << "[";
        for (size_t i = 0; i < shape[0]; ++i) {
            os << "\n  [ ";
            for (size_t j = 0; j < shape[1]; ++j) {
                os << tensor.data()[i * shape[1] + j] << " ";
            }
            os << "]";
        }
        os << "\n]";
        return os;
    }

    os << "Tensor shape: {";
    for (size_t i = 0; i < dims; ++i) {
        os << shape[i];
        if (i < dims - 1) {
            os << ", ";
        }
    }
    os << "}\n";

    const size_t LIMIT = 3;

    for (size_t layer = 0; layer < std::min(LIMIT, shape[0]); ++layer) {
        os << "[\n";
        for (size_t row = 0; row < std::min(LIMIT, shape[1]); ++row) {
            os << "   [ ";
            for (size_t col = 0; col < std::min(LIMIT, shape[2]); ++col) {
                os << tensor.data()[(layer * shape[1] + row) * shape[2] + col] << " ";
            }
            if (LIMIT * 2 < shape[2]) {
                os << "... ";

                for (size_t col = std::max(shape[2] - LIMIT, LIMIT); col < shape[2]; ++col) {
                    os << tensor.data()[(layer * shape[1] + row) * shape[2] + col] << " ";
                }
            }

            os << "]\n";
        }
        if (LIMIT * 2 < shape[1]) {
            os << "...\n";

            for (size_t row = std::max(shape[1] - LIMIT, LIMIT); row < shape[2]; ++row) {
                os << "   [ ";
                for (size_t col = 0; col < std::min(LIMIT, shape[2]); ++col) {
                    os << tensor.data()[(layer * shape[1] + row) * shape[2] + col] << " ";
                }
                if (LIMIT * 2 < shape[2]) {
                    os << "... ";

                    for (size_t col = std::max(shape[2] - LIMIT, LIMIT); col < shape[2]; ++col) {
                        os << tensor.data()[(layer * shape[1] + row) * shape[2] + col] << " ";
                    }
                }

                os << "]\n";
            }
        }
        os << "]\n\n";
    }

    if (LIMIT * 2 < shape[0]) {
        os << " ...\n ...\n ...\n\n";
        for (size_t layer = std::max(shape[0] - LIMIT, LIMIT); layer < shape[0]; ++layer) {
            os << "[\n";
            for (size_t row = 0; row < std::min(LIMIT, shape[1]); ++row) {
                os << "   [ ";
                for (size_t col = 0; col < std::min(LIMIT, shape[2]); ++col) {
                    os << tensor.data()[(layer * shape[1] + row) * shape[2] + col] << " ";
                }
                if (LIMIT * 2 < shape[2]) {
                    os << "... ";

                    for (size_t col = std::max(shape[2] - LIMIT, LIMIT); col < shape[2]; ++col) {
                        os << tensor.data()[(layer * shape[1] + row) * shape[2] + col] << " ";
                    }
                }

                os << "]\n";
            }
            if (LIMIT * 2 < shape[1]) {
                os << "   ...\n";

                for (size_t row = std::max(shape[1] - LIMIT, LIMIT); row < shape[2]; ++row) {
                    os << "   [ ";
                    for (size_t col = 0; col < std::min(LIMIT, shape[2]); ++col) {
                        os << tensor.data()[(layer * shape[1] + row) * shape[2] + col] << " ";
                    }
                    if (LIMIT * 2 < shape[2]) {
                        os << "... ";

                        for (size_t col = std::max(shape[2] - LIMIT, LIMIT); col < shape[2]; ++col) {
                            os << tensor.data()[(layer * shape[1] + row) * shape[2] + col] << " ";
                        }
                    }

                    os << "]\n";
                }
            }
            os << "]\n\n";
        }
    }
    os << "]";
    return os;
}