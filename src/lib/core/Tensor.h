#ifndef CPPKIT_LEARN_TENSOR_H
#define CPPKIT_LEARN_TENSOR_H

#pragma once

#include <vector>
#include <array>
#include <iostream>
#include <optional>

#include "iterator/Index.h"
#include "iterator/Iterator.h"
#include "iterator/Range.h"

const auto none = Range::None();

template<typename T>
class View;

/**
 * Тензор
 *
 * Может обладать произвольной размерностью, а также поддерживает индексирование и слайсинг.
 *
 * @tparam T тип данных, которые хранит тензор
 */
template<typename T>
class Tensor : public Iterable<T> {
private:
    std::vector<size_t> shape_;
    std::vector<T> data_;
public:
    /**
     * Создать пустой тензор
     *
     * @param shape Форма тензора.
     * @throws std::invalid_argument Выбрасывается, если имеются неположительные размерности.
     */
    explicit Tensor(std::vector<std::size_t> shape);

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

    /**
     * Получить элемент тензора по многомерному индексу.
     * @param index n-мерный индекс.
     * @throw std::out_of_range Выбрасывается, если индекс выходит за границы тензора.
     * @return Полученный элемент.
     */
    T &at(Index index) override;

    /**
     * Получить элемент тензора по набору одномерных индексов.
     *
     * @param indices Список индексов, по одному индексу для каждой размерности.
     * @return Полученный элемент.
     */
    T &operator[](const std::initializer_list<int> &indices);

    /**
     * Взять срез тензора.
     *
     * @param ranges Набор троек start, end, step.
     * @throw std::invalid_argument Выбрасывается, если количество переданных троек не совпадает с размерностью тензора.
     * @return Срез в виде представления.
     */
    View<T> slice(const std::vector<std::array<size_t, 3>> &ranges);

    View<T> operator[](const std::vector<Range> ranges);

    View<T> operator[](int index);

    [[nodiscard]] std::vector<size_t> shape() const override;

    [[nodiscard]] size_t dims() const;

    [[nodiscard]] std::vector<T> data() const;

    [[nodiscard]] size_t size() const;

    Iterator<T> begin() const override;

    Iterator<T> end() const override;

    Iterator<T> begin() override;

    Iterator<T> end() override;
};

#include "Tensor.tpp"

#endif //CPPKIT_LEARN_TENSOR_H
