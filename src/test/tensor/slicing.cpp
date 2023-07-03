#include "Tensor.h"

class TensorSlicingTest : public ::testing::Test {
protected:
    Tensor<double> *tensor5d{};

    void SetUp() override {
        tensor5d = new Tensor<double>({10, 10, 10, 10, 10});
        for (auto i = tensor5d->begin(); i != tensor5d->end(); ++i) {
            *i = i.index().toFlat();
        }
    }

    void TearDown() override {
        delete tensor5d;
    };
};


TEST_F(TensorSlicingTest, SliceByExplicitRanges_CorrectShape) {
    std::vector<std::array<size_t, 3>> ranges = {
            {3, 7, 1},
            {0, 6, 2},
            {7, 10, 1},
            {0, 10, 3},
            {5, 6, 1}
    };
    size_t dimsExpected = 5;
    std::vector<size_t> shapeExpected = {4, 3, 3, 4, 1};

    auto slice = tensor5d->slice(ranges);

    ASSERT_EQ(dimsExpected, slice.dims());
    ASSERT_EQ(shapeExpected, slice.shape());
    ASSERT_EQ(slice.operator[]({0, 0, 0, 0, 0}), 30705);
    ASSERT_EQ(slice.operator[]({0, 0, 0, 1, 0}), 30735);
    ASSERT_THROW(slice.operator[]({0, 0, 0, 0, 1}), std::out_of_range);
}

TEST_F(TensorSlicingTest, SliceOneProjection_CorrectShape){
    size_t dimsExpected = 4;
    std::vector<size_t> shapeExpected = {10, 10, 10, 10};

    auto subTensor = (*tensor5d)[2];

    ASSERT_EQ(dimsExpected, subTensor.actualDims());
    ASSERT_EQ(shapeExpected, subTensor.actualShape());
    ASSERT_EQ(subTensor.operator[]({0, 0, 0, 0}), 20000);
    ASSERT_EQ(subTensor.operator[]({0, 0, 0, 1}), 20001);
    ASSERT_THROW(subTensor.operator[]({0, 0, 0, 0, 0}), std::invalid_argument);
}


TEST_F(TensorSlicingTest, SliceMultiProjections_CorrectShape){
    size_t dimsExpected = 2;
    std::vector<size_t> shapeExpected = {10, 10};

    auto subTensor = (*tensor5d)[2][3][0];

    ASSERT_EQ(dimsExpected, subTensor.actualDims());
    ASSERT_EQ(shapeExpected, subTensor.actualShape());
    ASSERT_EQ(subTensor.operator[]({0, 0}), 23000);
    ASSERT_EQ(subTensor.operator[]({1, 1}), 23011);
    ASSERT_THROW(subTensor.operator[]({0, 0, 1}), std::invalid_argument);
}


TEST_F(TensorSlicingTest, SliceWithRanges_CorrectShape){
    size_t dimsExpected = 5;
    std::vector<size_t> shapeExpected = {7, 3, 2, 5, 10};

    auto view = (*tensor5d)[{{3}, {4, 7}, {2, 8, 3}, {none, 5}}];

    ASSERT_EQ(view.operator[]({0, 0, 0, 0, 0}), 34200);
    ASSERT_THROW(view.operator[]({0, 0, 0, 0}), std::invalid_argument);
    ASSERT_EQ(dimsExpected, view.actualDims());
    ASSERT_EQ(shapeExpected, view.actualShape());
}
