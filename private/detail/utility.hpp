#pragma once

namespace anton::math::detail {
    template<typename T>
    constexpr void swap(T& a, T& b) {
        T tmp = static_cast<T&&>(a);
        a = static_cast<T&&>(b);
        b = static_cast<T&&>(tmp);
    }
} // namespace anton::math::detail
