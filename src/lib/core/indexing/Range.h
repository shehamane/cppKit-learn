#ifndef CPPKIT_LEARN_RANGE_H
#define CPPKIT_LEARN_RANGE_H

#pragma once

#include <cstddef>
#include <tuple>

struct Range {
public:
    template<typename Begin, typename End>
    Range(Begin begin, End end, std::size_t step);

    template<typename Begin, typename End>
    Range(Begin begin, End end);

    Range(std::size_t begin);

    struct None {
    public:
        None(){};

        bool operator==(None& other){
            return true;
        }
    };

    [[nodiscard]] std::tuple<int, int, size_t> decompose() const;

private:
    int begin_ = 0;
    int end_ = 0;
    size_t step_;
};

#include "Range.tpp"

#endif //CPPKIT_LEARN_RANGE_H
