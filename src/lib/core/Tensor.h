#ifndef CPPKIT_LEARN_TENSOR_H
#define CPPKIT_LEARN_TENSOR_H

#pragma once

#include <vector>
#include <array>
#include <iostream>
#include <optional>
#include <string>
#include <iostream>
#include <type_traits>

#include "indexing/Index.h"
#include "indexing/Iterator.h"
#include "indexing/Range.h"

#define none Range::None()
#define Shape std::vector<size_t>

template<typename T>
class View;

/**
 * Тензор произвольной размерности
 *
 * @tparam T тип данных, которые хранит тензор
 */
template<typename T>
class Tensor : public NDArray<T> {
protected:
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

    Tensor<T> matmul(const Tensor<T> &other) const;


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
    // Static initializers

    static Tensor<T> full(Shape shape, T val);

    template<
            typename V = T,
            typename = typename std::enable_if_t<std::is_arithmetic_v<V>>
    >
    static Tensor<T> zeros(Shape shape);

    template<
            typename V = T,
            typename = typename std::enable_if_t<std::is_arithmetic_v<V>>
    >
    static Tensor<T> ones(Shape shape);

    template<
            typename V = T,
            typename = typename std::enable_if_t<std::is_arithmetic_v<V>>
    >
    static Tensor<T> range(T from, T to, T step = 1);

};

#include "Tensor.tpp"

#endif //CPPKIT_LEARN_TENSOR_H
