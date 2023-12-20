#include "Range.h"

#include <functional>
#include <stdexcept>

template<typename Begin, typename End>
Range::Range(Begin begin, End end, std::size_t step) {
    if constexpr (std::is_integral_v<Begin>) {
        begin_ = begin;
    }
    if constexpr (std::is_integral_v<End>) {
        end_ = end;
    }
    if (!step_){
        throw std::invalid_argument("Zero range step");
    }
    step_ = step;
}

template<typename Begin, typename End>
Range::Range(Begin begin, End end) : Range(begin, end, 1) {}

Range::Range(std::size_t begin) : Range(begin, 0, 1) {}

[[nodiscard]] std::tuple<int, int, size_t> Range::decompose() const{
    return {begin_, end_, step_};
}