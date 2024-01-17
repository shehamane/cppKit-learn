#ifndef CPPKIT_LEARN_TENSOR_H
#define CPPKIT_LEARN_TENSOR_H

#pragma once

#include <vector>
#include <array>
#include <iostream>
#include <optional>
#include <string>
#include <iostream>

#include "indexing/Index.h"
#include "indexing/Iterator.h"
#include "indexing/Range.h"

#define none Range::None()

template<typename T>
class View;

/**
 * Тензор произвольной размерности
 *
 * @tparam T тип данных, которые хранит тензор
 */
template<typename T>
class Tensor : public NDArray<T> {
private:
    std::vector<size_t> shape_;
    std::vector<T> data_;
public:
    //***********************************************************
    // Constructors
    /**
     * Создать пустой тензор
     *
     * @param shape Форма тензора.
     * @throws std::invalid_argument Выбрасывается, если имеются неположительные размерности.
     * @example
     * Создание матрицы 3x3:
     * <pre>
     * Tensor<int> t({3, 3});
     * </pre>
     */
    explicit Tensor(std::vector<std::size_t> shape);


    Tensor(std::vector<std::size_t> shape, std::vector<T> data);

    /**
     * Создать тензор, аналогичный представлению. Тензор будет обладать той же формой, а данные будут скопированы.
     *
     * @param view Представление.
     */
    Tensor(View<T> &view);

    /**
     * Создать тензор, аналогичный r-value-Представлению. Тензор будет обладать той же формой, а
     * данные будут скопированы.
     *
     * @param view
     */
    Tensor(const View<T> &view);

    Tensor(const Tensor<T> &other);



    //***********************************************************
    // Indexing
    /**
     * Получить элемент тензора по многомерному индексу.
     * @param index объект класса Index.
     * @throw std::out_of_range Выбрасывается, если индекс выходит за границы тензора.
     * @return Полученный элемент.
     */
    T at(Index index) const override;

    T &operator[](Index index);


    /**
     * Получить элемент тензора по набору одномерных индексов.
     *
     * @param indices Список индексов, длина списка должна соответствовать размерности тензора.
     * @return Полученный элемент.
     */
    T &operator[](const std::initializer_list<int> &indices);



    //***********************************************************
    // Slicing
    /**
     * Взять срез тензора.
     *
     * @param ranges Список троек start, end, step. Размер списка должен соответствовать размерности тензора.
     * @throw std::invalid_argument Выбрасывается, если количество переданных троек не совпадает с размерностью тензора.
     * @return Срез в виде представления.
     */
    View<T> slice(const std::vector<Range> ranges);

    /**
     * Получить подтензор меньшего порядка по индексу.<br><br>
     *
     * Аналогично взятию среза по первому измерению с интервалом (i, i+1).
     *
     * @param index Индекс подтензора
     * @return Срез в виде представления
     */
    View<T> operator[](int index);



    //***********************************************************
    // Getters
    /**
     * Получить форму тензора.
     *
     * @return Форма тензора в виде списка размерностей.
     */
    [[nodiscard]] std::vector<size_t> shape() const override;

    /**
     * Получить размерность тензора.
     *
     * @return Размерность тензора.
     */
    [[nodiscard]] size_t dims() const;

    /**
     * Получить хранимые в тензоре данные
     * @return Данные в одномерном списке.
     */
    [[nodiscard]] std::vector<T> data() const;

    /**
     * Получить общимй размер тензора <br><br>
     *
     * Вычисляется как произведение размерностей каждого измерения.
     * @return Общий размер тензора
     */
    [[nodiscard]] size_t size() const;

    /**
     * Получить указатель на начало тензора.
     * @return Объект класса Iterator, указывающий на начало тензора.
     */
    Iterator<T> begin() const override;

    /**
     * Получить указатель на конец тензора.
     * @return Объект класса Iterator, указывающий на конец тензора.
     */
    Iterator<T> end() const override;

    /**
     * Получить указатель на начало тензора.
     * @return Объект класса Iterator, указывающий на начало тензора.
     */
    Iterator<T> begin() override;

    /**
     * Получить указатель на начало тензора.
     * @return Объект класса Iterator, указывающий на начало тензора.
     */
    Iterator<T> end() override;


    //***********************************************************
    // Unary operations
    Tensor<T> transpose();

    Tensor<T> reshape(std::vector<size_t> newShape);


    //***********************************************************
    // Binary operations
    Tensor<T> operator+(const Tensor<T> &other) const;

    Tensor<T> operator-(const Tensor<T> &other) const;

    Tensor<T> operator*(const Tensor<T> &other) const;

    Tensor<T> operator/(const Tensor<T> &other) const;

    Tensor<T> operator%(const Tensor<T> &other) const;

    Tensor<T> pow(const Tensor<T> &other) const;


    //***********************************************************
    // Binary operations with numbers
    template<
            typename V,
            typename = typename std::enable_if<std::is_arithmetic<V>::value>::type
    >
    Tensor<T> operator+(const V &other) const;

    template<
            typename V,
            typename = typename std::enable_if<std::is_arithmetic<V>::value>::type
    >
    Tensor<T> operator-(const V &other) const;

    template<
            typename V,
            typename = typename std::enable_if<std::is_arithmetic<V>::value>::type
    >
    Tensor<T> operator*(const V &other) const;

    template<
            typename V,
            typename = typename std::enable_if<std::is_arithmetic<V>::value>::type
    >
    Tensor<T> operator/(const V &other) const;

    template<
            typename V,
            typename = typename std::enable_if<std::is_arithmetic<V>::value>::type
    >
    Tensor<T> operator%(const V &other) const;

    template<
            typename V,
            typename = typename std::enable_if<std::is_arithmetic<V>::value>::type
    >
    Tensor<T> pow(const V &other) const;


    //***********************************************************
    // Format

    friend std::ostream& operator<<(std::ostream &os, const Tensor<T>& tensor) {
        std::vector<size_t> shape = tensor.shape();
        size_t dims = shape.size();
        if (dims == 1) {
            os << "[ ";
            for (size_t i = 0; i < shape[0]; ++i) {
                os << tensor.data_[i] << " ";
            }
            os << "]";
            return os;
        }

        if (dims == 2) {
            os << "[";
            for (size_t i = 0; i < shape[0]; ++i) {
                os << "\n  [ ";
                for (size_t j = 0; j < shape[1]; ++j) {
                    os << tensor.data_[i * shape[1] + j] << " ";
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

        size_t max_layers = 5;
        size_t max_rows = 5;
        size_t max_cols = 5;

        os << "[";
        for (size_t layer = 0; layer < std::min(max_layers, shape[0]); ++layer) {
            if (layer > 0) {
                os << "\n ...\n";
            }
            os << " Layer " << layer << ":\n";
            for (size_t row = 0; row < std::min(max_rows, shape[1]); ++row) {
                os << "  [ ";
                for (size_t col = 0; col < std::min(max_cols, shape[2]); ++col) {
                    os << tensor.data_[(layer * shape[1] + row) * shape[2] + col] << " ";
                }
                if (max_cols < shape[2]) {
                    os << "... ";
                }
                os << "]\n";
            }
            if (max_rows < shape[1]) {
                os << "  ...\n";
            }
        }

        if (max_layers < shape[0]) {
            os << " ...\n";
            os << " Layer " << shape[0] - 1 << ":\n";
            for (size_t row = 0; row < std::min(max_rows, shape[1]); ++row) {
                os << "  [ ";
                for (size_t col = 0; col < std::min(max_cols, shape[2]); ++col) {
                    os << tensor.data_[(shape[0] - 1) * shape[1] * shape[2] + row * shape[2] + col] << " ";
                }
                if (max_cols < shape[2]) {
                    os << "... ";
                }
                os << "]\n";
            }
            if (max_rows < shape[1]) {
                os << "  ...\n";
            }
        }
        os << "]";
        return os;
    }
};

#include "Tensor.tpp"

#endif //CPPKIT_LEARN_TENSOR_H
