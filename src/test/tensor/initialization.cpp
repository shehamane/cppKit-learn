#include "googletest/googletest/include/gtest/gtest.h"

#include "Tensor.h"
#include "View.h"

TEST(TensorInitTest, Init_Int_CorrectShape) {
    std::vector<size_t> shape = {2, 2};
    Tensor<int> tensor(shape);

    EXPECT_EQ(tensor.size(), 4);
    EXPECT_EQ(tensor.dims(), 2);
    EXPECT_EQ(tensor.shape(), shape);
}

TEST(TensorInitTest, Init_double_CorrectShape) {
    std::vector<size_t> shape = {2, 2, 2, 2, 2, 2};
    Tensor<double> tensor(shape);

    EXPECT_EQ(tensor.size(), 64);
    EXPECT_EQ(tensor.dims(), 6);
    EXPECT_EQ(tensor.shape(), shape);
}

TEST(TensorInitTest, Init_SingleValue_CorrectShape) {
    std::vector<size_t> shape = {1};
    Tensor<double> tensor(shape);

    EXPECT_EQ(tensor.size(), 1);
    EXPECT_EQ(tensor.dims(), 1);
    EXPECT_EQ(tensor.shape(), shape);
}

TEST(TensorInitTest, Init_WithZeroShape_ThrowException) {
    ASSERT_THROW(Tensor<int>({0}), std::invalid_argument);
}

TEST(TensorInitTest, Init_FromView_EqualData) {
    Tensor<double> tensor1({5, 5, 5});
    for (Index i = Index::begin(tensor1.shape()); i != Index::end(tensor1.shape()); i.next()) {
        tensor1.at(i) = (double) i.toFlat();
    }
    std::vector<size_t> view_shape = {3, 3, 3};
    View<double> view(tensor1, {{0, 3, 1},
                                {0, 3, 1},
                                {0, 3, 1}});
    Tensor<double> tensor2 = view;

    EXPECT_EQ(tensor2.size(), 27);
    EXPECT_EQ(tensor2.dims(), 3);
    EXPECT_EQ(tensor2.shape(), view_shape);
    for (Index i = Index::begin(tensor2.shape()); i != Index::end(tensor2.shape()); i.next()) {
        EXPECT_EQ(tensor2.at(i), view.at(i));
    }
}

TEST(TensorInitTest, Init_FromConstView_EqualData) {
    Tensor<double> tensor1({5, 5, 5});
    for (Index i = Index::begin(tensor1.shape()); i != Index::end(tensor1.shape()); i.next()) {
        tensor1.at(i) = (double) i.toFlat();
    }
    std::vector<size_t> viewShape = {5, 5};
    Tensor<double> tensor2 = tensor1[3];

    EXPECT_EQ(tensor2.size(), 25);
    EXPECT_EQ(tensor2.dims(), 2);
    EXPECT_EQ(tensor2.shape(), viewShape);
    for (Index i = Index::begin(tensor2.shape()); i != Index::end(tensor2.shape()); i.next()) {
        EXPECT_EQ(tensor2.at(i), tensor1[3].at(i));
    }
}