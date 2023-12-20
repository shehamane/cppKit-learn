#ifndef CPPKIT_LEARN_TENSOR_H
#define CPPKIT_LEARN_TENSOR_H

#pragma once

#include <vector>
#include <array>
#include <iostream>
#include <optional>

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

    /**
     * Получить элемент тензора по многомерному индексу.
     * @param index объект класса Index.
     * @throw std::out_of_range Выбрасывается, если индекс выходит за границы тензора.
     * @return Полученный элемент.
     */
    T &at(Index index) override;

    /**
     * Получить элемент тензора по набору одномерных индексов.
     *
     * @param indices Список индексов, длина списка должна соответствовать размерности тензора.
     * @return Полученный элемент.
     */
    T &operator[](const std::initializer_list<int> &indices);

    /**
     * Взять срез тензора.
     *
     * @param ranges Список троек start, end, step. Размер списка должен соответствовать размерности тензора.
     * @throw std::invalid_argument Выбрасывается, если количество переданных троек не совпадает с размерностью тензора.
     * @return Срез в виде представления.
     */
    View<T> slice(const std::vector<std::array<size_t, 3>> &ranges);

    /**
     * Взять срез тензора. <br><br>
     * Могут быть переданы интервалы для первых k измерений. В этом случае по остальным измерения срез будет получен полностью.
     *
     * Для каждой размерности может быть передана: <br>
     * <ul>
     * <li> тройка (start, end, step) </li>
     * <li> пара (start, end), при этом устанавливается единичный шаг </li>
     * <li> только (start, ), при этом устанавливается единичный шаг, а срез будет взять до конца измерения </li>
     * </ul>
     * В случае необходимости, индексы могут быть пропущены: <br>
     * <ul>
     * <li> Если в качестве start передать значение none, то срез будет получен от начала размерности. </li>
     * <li> Если в качестве end передать значение none, то срез будет получен до конца размерности. </li>
     * </ul>
     * @param ranges Список интервалов.
     * @return Срез в виде представления
     */
    View<T> operator[](const std::vector<Range> ranges);

    /**
     * Получить подтензор меньшего порядка по индексу.<br><br>
     *
     * Аналогично взятию среза по первому измерению с интервалом (i, i+1).
     *
     * @param index Индекс подтензора
     * @return Срез в виде представления
     */
    View<T> operator[](int index);

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

    // Binary operations
    Tensor<T> operator+(const Tensor<T> &other) const;

    Tensor<T> operator-(const Tensor<T> &other) const;

    Tensor<T> operator*(const Tensor<T> &other) const;

    Tensor<T> operator/(const Tensor<T> &other) const;

    Tensor<T> operator%(const Tensor<T> &other) const;

    Tensor<T> pow(const Tensor<T> &other) const;
};

#include "Tensor.tpp"

#endif //CPPKIT_LEARN_TENSOR_H
