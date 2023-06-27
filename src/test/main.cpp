#include "googletest/googletest/include/gtest/gtest.h"

#include "tensor/initialization.cpp"
#include "tensor/indexing.cpp"
#include "tensor/slicing.cpp"
#include "view/initialization.cpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}