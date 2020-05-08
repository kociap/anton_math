#ifndef ANTON_MATH_DETAIL_UTILITY_HPP_INCLUDE
#define ANTON_MATH_DETAIL_UTILITY_HPP_INCLUDE

namespace anton::math::detail {
    template<typename T>
    constexpr void swap(T& a, T& b) {
        T tmp = static_cast<T&&>(a);
        a = static_cast<T&&>(b);
        b = static_cast<T&&>(tmp);
    }
}

#endif // !ANTON_MATH_DETAIL_UTILITY_HPP_INCLUDE
