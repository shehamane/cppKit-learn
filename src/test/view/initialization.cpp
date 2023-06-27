#include "googletest/googletest/include/gtest/gtest.h"

#include "Tensor.h"
#include "View.h"

class Tensor3DTest : public ::testing::Test {
protected:
    Tensor<double> *tensor3d{};

    void SetUp() override {
        tensor3d = new Tensor<double>({5, 6, 7});
        for (auto i = tensor3d->begin(); i != tensor3d->end(); ++i) {
            *i = i.index().toFlat();
        }
    }

    void TearDown() override {
        delete tensor3d;
    };
};

TEST_F(Tensor3DTest, Init_WithConstructor) {
    View<double> view(*tensor3d, {{1, 4, 1}, {0, 5, 1}, {0, 6, 2}});
    std::vector<size_t> shapeExpected = {3, 5, 3};

    ASSERT_EQ(view.shape(), shapeExpected);
    ASSERT_EQ(view.dims(), 3);
    ASSERT_EQ(view.operator[]({0, 0, 0}), 42);
}