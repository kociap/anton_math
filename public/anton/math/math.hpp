#pragma once

// Safety measures
#undef max
#undef min
#undef far
#undef near

#include <anton/types.hpp>

extern "C" {
    #if defined(_WIN32) || defined(_WIN64)
        // intrin.h

        unsigned char _BitScanReverse(unsigned long *_Index, unsigned long _Mask);
        unsigned char _BitScanReverse64(unsigned long *_Index, unsigned long long _Mask);
        int __cdecl _mm_popcnt_u32(unsigned int);
        long long __cdecl _mm_popcnt_u64(unsigned long long);
    #endif
}

namespace anton::math {
    constexpr f32 pi = 3.1415926f;
    constexpr f32 half_pi = 1.5707964f;
    constexpr f32 two_pi = 6.2831853f;
    constexpr f32 deg_to_rad = pi / 180.0f;
    constexpr f32 rad_to_deg = 180.0f / pi;
    // Largest representable value
    constexpr f32 largest_representable = 3.402823466e+38f;
    // Smallest number such that 1.0 + epsilon != 1.0
    constexpr f32 epsilon = 1.192092896e-07f;
    // __builtin_huge_valf is supported by all major compilers.
    constexpr f32 infinity = __builtin_huge_valf();
    constexpr f32 golden_ratio = 1.61803398f;

    // radians
    // Converts degrees to radians.
    //
    [[nodiscard]] constexpr f32 radians(f32 const degrees) {
        return degrees * deg_to_rad;
    }

    // degrees
    // Converts radians to degrees.
    //
    [[nodiscard]] constexpr f32 degrees(f32 const radians) {
        return radians * rad_to_deg;
    }

    // is_nan
    // Checks whether v is nan.
    //
    [[nodiscard]] bool is_nan(f32 v);

    [[nodiscard]] f32 pow(f32 base, f32 exp);

    [[nodiscard]] f32 sqrt(f32 a);

    [[nodiscard]] f32 cbrt(f32 a);

    [[nodiscard]] f32 inv_sqrt(f32 a);

    [[nodiscard]] f32 sign(f32 a);

    [[nodiscard]] f32 sin(f32 angle);

    [[nodiscard]] f32 asin(f32 angle);

    [[nodiscard]] f32 cos(f32 angle);

    [[nodiscard]] f32 acos(f32 angle);

    [[nodiscard]] f32 tan(f32 angle);

    [[nodiscard]] f32 atan(f32 angle);

    [[nodiscard]] f32 atan2(f32 y, f32 x);

    // exp
    // Calculate e^n
    //
    [[nodiscard]] f32 exp(f32 n);

    // log
    // Compute natural logarithm (base-e).
    //
    [[nodiscard]] f32 log(f32 v);

    // log10
    // Compute base-10 logarithm.
    //
    [[nodiscard]] f32 log10(f32 v);

    // log2
    // Compute base-2 logarithm.
    //
    [[nodiscard]] f32 log2(f32 v);

    // ilog2
    // Computes the floor of logarithm base 2 of v.
    //
    [[nodiscard]] u32 ilog2(u32 v);

    [[nodiscard]] u64 ilog2(u64 v);

    // ilog10
    // Computes the floor of logarithm base 10 of v.
    // Returns 0 for ilog10(0).
    //
    [[nodiscard]] u64 ilog10(u64 v);

    // mod
    // Computes the floating point remainder of the operation x/y.
    // The result has the same sign as x.
    //
    [[nodiscard]] f32 mod(f32 x, f32 y);

    [[nodiscard]] f32 round(f32 x);

    // round_to_nearest
    // Rounds x to the nearest multiple of b.
    // b must be positive.
    //
    [[nodiscard]] f32 round_to_nearest(f32 x, f32 b);

    [[nodiscard]] f32 floor(f32 x);

    [[nodiscard]] f32 ceil(f32 x);

    [[nodiscard]] f32 fract(f32 x);

    template<typename T>
    [[nodiscard]] constexpr T abs(T const a) {
        return a < T(0) ? -a : a;
    }

    template<typename T>
    [[nodiscard]] constexpr T max(T const a, T const b) {
        return a > b ? a : b;
    }

    template<typename T, typename... VT>
    [[nodiscard]] constexpr T max(T const& arg1, T const& arg2, T const& arg3, VT const&... args) {
        constexpr i64 array_size = sizeof...(VT) + 3;
        T const* arg_array[array_size] = {&arg1, &arg2, &arg3, &args...};
        T const* max_elem = arg_array[0];
        for(i64 i = 1; i < array_size; ++i) {
            if(*arg_array[i] > *max_elem) {
                max_elem = arg_array[i];
            }
        }
        return *max_elem;
    }

    template<typename T>
    [[nodiscard]] constexpr T min(T const a, T const b) {
        return a < b ? a : b;
    }

    template<typename T, typename... VT>
    [[nodiscard]] constexpr T min(T const& arg1, T const& arg2, T const& arg3, VT const&... args) {
        constexpr i64 array_size = sizeof...(VT) + 3;
        T const* arg_array[array_size] = {&arg1, &arg2, &arg3, &args...};
        T const* min_elem = arg_array[0];
        for(i64 i = 1; i < array_size; ++i) {
            if(*arg_array[i] < *min_elem) {
                min_elem = arg_array[i];
            }
        }
        return *min_elem;
    }

    template<typename T>
    [[nodiscard]] constexpr T clamp(T const x, T const lower_limit, T const upper_limit) {
        return min(max(x, lower_limit), upper_limit);
    }

    // is_almost_zero
    // Determines whether the value is almost equal to 0 within given tolerance.
    //
    [[nodiscard]] bool is_almost_zero(f32 value, f32 tolerance = 0.000001f);

    [[nodiscard]] f32 step_to_value(f32 current, f32 target, f32 change);

    // lerp
    // Computes the linear interpolation between a and b for the parameter t in the interval [0, 1].
    //
    [[nodiscard]] f32 lerp(f32 a, f32 b, f32 t);

    // smoothstep
    //
    [[nodiscard]] f32 smoothstep(f32 edge0, f32 edge1, f32 x);

    // smootherstep
    // Improved version of smoothstep that has zero 1st and 2nd order derivatives at egde0 and edge1.
    //
    // Returns 0 if x <= edge0, 1 if x >= edge1, otherwise computes 6x^5 - 15x^4 + 10x^3
    // with x rescaled to range [0.0, 1.0].
    //
    [[nodiscard]] f32 smootherstep(f32 edge0, f32 edge1, f32 x);

    // popcount
    // Counts the number of set bits in v.
    //
    [[nodiscard]] inline u8 popcount(u8 v) {
        return _mm_popcnt_u32(v);
    }

    [[nodiscard]] inline u16 popcount(u16 v) {
        return _mm_popcnt_u32(v);
    }

    [[nodiscard]] inline u32 popcount(u32 v) {
        return _mm_popcnt_u32(v);
    }

    [[nodiscard]] inline u64 popcount(u64 v) {
        return _mm_popcnt_u64(v);
    }

    // clz
    // Counts leading zeros.
    //
    // Returns:
    // The number of leading zeros. If the number is 0, returns bit count.
    //
    [[nodiscard]] inline u8 clz(u8 v) {
        #if ANTON_COMPILER_CLANG
            return (v != 0 ? __builtin_clz(v) - 24 : 8);
        #else
            unsigned long index = 0;
            if(_BitScanReverse(&index, v)) {
                return 7 - index;
            } else {
                return 8;
            }
        #endif
    }

    [[nodiscard]] inline u16 clz(u16 v) {
        #if ANTON_COMPILER_CLANG
            return (v != 0 ? __builtin_clz(v) - 16 : 16);
        #else
            unsigned long index = 0;
            if(_BitScanReverse(&index, v)) {
                return 15 - index;
            } else {
                return 16;
            }
        #endif
    }

    [[nodiscard]] inline u32 clz(u32 v) {
        #if ANTON_COMPILER_CLANG
            return (v != 0 ? __builtin_clz(v) : 32);
        #else
            unsigned long index = 0;
            if(_BitScanReverse(&index, v)) {
                return 31 - index;
            } else {
                return 32;
            }
        #endif
    }

    [[nodiscard]] inline u64 clz(u64 v) {
        #if ANTON_COMPILER_CLANG
            return (v != 0 ? __builtin_clzll(v) : 64);
        #else
            unsigned long index = 0;
            if(_BitScanReverse64(&index, v)) {
                return 63 - index;
            } else {
                return 64;
            }
        #endif
    }
} // namespace anton::math
