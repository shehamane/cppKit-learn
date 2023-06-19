#include "Tensor.h"

class TensorTest : public ::testing::Test {
protected:
    Tensor<double> *tensor3d{};
    Tensor<int> *tensor1d{};

    void SetUp() override {
        tensor3d = new Tensor<double>({5, 6, 7});
        for (auto i = tensor3d->begin(); i != tensor3d->end(); ++i) {
            *i = i.index().toFlat();
        }

        tensor1d = new Tensor<int>({100});
        for (int i = 0; i < 100; ++i) {
            (*tensor1d)[{i}] = i;
        }
    }

    void TearDown() override {
        delete tensor3d;
        delete tensor1d;
    };
};

TEST_F(TensorTest, GetByIndices_FirstElem_Returns0) {
    ASSERT_EQ(tensor3d->operator[]({0, 0, 0}), 0);
    ASSERT_EQ(tensor1d->operator[](0), 0);
}

TEST_F(TensorTest, GetByIndicies_LastElem_Returns209) {
    ASSERT_EQ(tensor3d->operator[]({4, 5, 6}), 209);
    ASSERT_EQ(tensor1d->operator[](99), 99);
}

TEST_F(TensorTest, SetByIndicies_Elem_Correct) {
    double testValue3d = 999;
    int testValue1d = 127;

    (*tensor3d)[{4, 5, 6}] = testValue3d;
    (*tensor1d)[{10}] = testValue1d;

    ASSERT_EQ(tensor3d->operator[]({4, 5, 6}), testValue3d);
    ASSERT_EQ(tensor1d->operator[](10), testValue1d);
}

TEST_F(TensorTest, GetAndSet_ByIndex_ChangesApplied) {
    Index index(tensor3d->shape(), {2, 3, 4});

    auto val = tensor3d->at(index);
    tensor3d->at(index) = 933;

    ASSERT_EQ(val, index.toFlat());
    ASSERT_EQ(tensor3d->at(index), 933);
    ASSERT_EQ(tensor3d->operator[]({2, 3, 4}), 933);
    ASSERT_EQ((int) (*tensor3d)[2][3][4], 933);
}

TEST_F(TensorTest, IterateOverAll_WithForeach_CorrectOrder) {
    int i = 0;
    for (auto val: *tensor1d) {
        ASSERT_EQ(val, i++);
    }
    i = 0;
    for (auto val: *tensor3d) {
        ASSERT_EQ(val, i++);
    }
}

TEST_F(TensorTest, IterateOverAll_DoSomeChanges_ChangesApplied) {
    auto tensor1dIt = tensor1d->begin();
    while (tensor1dIt != tensor1d->end()){
        *tensor1dIt += 1;
        ++tensor1dIt;
    }

    auto tensor3dIt = tensor3d->begin();
    while (tensor3dIt != tensor3d->end()){
        *tensor3dIt *= 2;
        ++tensor3dIt;
    }

    int i = 0;
    for (auto val: *tensor1d) {
        ASSERT_EQ(val, i+1);
        ++i;
    }

    i = 0;
    for (auto val: *tensor3d) {
        ASSERT_EQ(val, i*2);
        ++i;
    }
}
