#include "googletest/googletest/include/gtest/gtest.h"

#include "Tensor.h"

class TensorTest : public ::testing::Test {
protected:
    Tensor<double> *tensor;


    void SetUp() override {
        tensor = new Tensor<double>({5, 6, 7});
        for (auto i = tensor->begin(); i != tensor->end(); ++i) {
            *i = i.index().toFlat();
        }
    }

    void TearDown() override {
        delete tensor;
    };
};

TEST_F(TensorTest, GetByIndices_FirstElem_Returns0) {
    auto val = (*tensor)[{0, 0, 0}];
    ASSERT_EQ(val, 0);
}

TEST_F(TensorTest, GetByIndicies_LastElem_Returns209){
    auto val = (*tensor)[{4, 5, 6}];
    ASSERT_EQ(val, 209);
}
