#include <anton/math/math.hpp>

// Forward declarations from math.h

extern "C" {
    #if defined(_WIN32) || defined(_WIN64)
    #    define ANTON_NOEXCEPT
    #    define ANTON_CRT_IMPORT __declspec(dllimport)
    #else
    #    define ANTON_NOEXCEPT noexcept
    #    define ANTON_CRT_IMPORT
    #endif

    ANTON_CRT_IMPORT float powf(float, float) ANTON_NOEXCEPT;
    ANTON_CRT_IMPORT float sqrtf(float) ANTON_NOEXCEPT;
    ANTON_CRT_IMPORT float cbrtf(float) ANTON_NOEXCEPT;
    ANTON_CRT_IMPORT float fmodf(float, float) ANTON_NOEXCEPT;
    ANTON_CRT_IMPORT float roundf(float) ANTON_NOEXCEPT;
    ANTON_CRT_IMPORT float floorf(float) ANTON_NOEXCEPT;
    ANTON_CRT_IMPORT float ceilf(float) ANTON_NOEXCEPT;
    ANTON_CRT_IMPORT float modff(float, float*) ANTON_NOEXCEPT;
    ANTON_CRT_IMPORT float sinf(float) ANTON_NOEXCEPT;
    ANTON_CRT_IMPORT float cosf(float) ANTON_NOEXCEPT;
    ANTON_CRT_IMPORT float tanf(float) ANTON_NOEXCEPT;
    ANTON_CRT_IMPORT float asinf(float) ANTON_NOEXCEPT;
    ANTON_CRT_IMPORT float acosf(float) ANTON_NOEXCEPT;
    ANTON_CRT_IMPORT float atanf(float) ANTON_NOEXCEPT;
    ANTON_CRT_IMPORT float atan2f(float, float) ANTON_NOEXCEPT;
    ANTON_CRT_IMPORT float expf(float) ANTON_NOEXCEPT;
    ANTON_CRT_IMPORT float logf(float) ANTON_NOEXCEPT;
    ANTON_CRT_IMPORT float log10f(float) ANTON_NOEXCEPT;
    ANTON_CRT_IMPORT float log2f(float) ANTON_NOEXCEPT;

    #undef ANTON_CRT_IMPORT
    #undef ANTON_NOEXCEPT
}

namespace anton::math {
    bool is_nan(f32 v) {
        // nan does not compare equal to anything, including itself.
        return v != v;
    }

    f32 pow(f32 const base, f32 const exp) {
        return ::powf(base, exp);
    }

    f32 sqrt(f32 const a) {
        return ::sqrtf(a);
    }

    f32 cbrt(f32 const a) {
        return ::cbrtf(a);
    }

    f32 inv_sqrt(f32 const a) {
        return 1 / sqrt(a);
    }

    f32 sign(f32 const a) {
        return static_cast<f32>((a > 0.0f) - (a < 0.0f));
    }

    f32 sin(f32 const angle) {
        return ::sinf(angle);
    }

    f32 asin(f32 const angle) {
        return ::asinf(angle);
    }

    f32 cos(f32 const angle) {
        return ::cosf(angle);
    }

    f32 acos(f32 const angle) {
        return ::acosf(angle);
    }

    f32 tan(f32 const angle) {
        return ::tanf(angle);
    }

    f32 atan(f32 const angle) {
        return ::atanf(angle);
    }

    f32 atan2(f32 const y, f32 const x) {
        return ::atan2f(y, x);
    }

    // exp
    // Calculate e^n
    //
    f32 exp(f32 const n) {
        return ::expf(n);
    }

    // log
    // Compute natural logarithm (base-e).
    //
    f32 log(f32 const v) {
        return ::logf(v);
    }

    // log10
    // Compute base-10 logarithm.
    //
    f32 log10(f32 const v) {
        return ::log10f(v);
    }

    // log2
    // Compute base-2 logarithm.
    //
    f32 log2(f32 const v) {
        return ::log2f(v);
    }

    // ilog2
    // Computes the floor of logarithm base 2 of v.
    //
    u32 ilog2(u32 const v) {
        return 32 - clz(v) - 1;
    }

    u64 ilog2(u64 const v) {
        return 64 - clz(v) - 1;
    }

    // ilog10
    // Computes the floor of logarithm base 10 of v.
    // Returns 0 for ilog10(0).
    //
    u64 ilog10(u64 const v) {
        u64 powers_of_10[] = {1ULL,
                              10ULL,
                              100ULL,
                              1000ULL,
                              10000ULL,
                              100000ULL,
                              1000000ULL,
                              10000000ULL,
                              100000000ULL,
                              1000000000ULL,
                              10000000000ULL,
                              100000000000ULL,
                              1000000000000ULL,
                              10000000000000ULL,
                              100000000000000ULL,
                              1000000000000000ULL,
                              10000000000000000ULL,
                              100000000000000000ULL,
                              1000000000000000000ULL,
                              10000000000000000000ULL};
        u64 const temp = (ilog2(v) + 1) * 1233 >> 12;
        return temp - (v < powers_of_10[temp]);
    }

    // mod
    // Computes the floating point remainder of the operation x/y.
    // The result has the same sign as x.
    //
    f32 mod(f32 const x, f32 const y) {
        return fmodf(x, y);
    }

    f32 round(f32 const x) {
        return ::roundf(x);
    }

    f32 round_to_nearest(f32 const x, f32 const b) {
        return round(x / b) * b;
    }

    f32 floor(f32 const x) {
        return ::floorf(x);
    }

    f32 ceil(f32 const x) {
        return ::ceilf(x);
    }

    f32 fract(f32 const x) {
        f32 integral_part;
        return ::modff(x, &integral_part);
    }

    // is_almost_zero
    // Determines whether the value is almost equal to 0 within given tolerance.
    //
    bool is_almost_zero(f32 const value, f32 const tolerance) {
        return math::abs(value) <= tolerance;
    }

    f32 step_to_value(f32 const current, f32 const target, f32 const change) {
        f32 delta = target - current;
        if (abs(delta) > change) {
            return current + sign(delta) * change;
        } else {
            return target;
        }
    }

    f32 lerp(f32 const a, f32 const b, f32 const t) {
        return (1.0f - t) * a + t * b;
    }

    f32 smoothstep(f32 const edge0, f32 const edge1, f32 x) {
        x = clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
        return x * x * (3.0f - 2.0f * x);
    }

    f32 smootherstep(f32 const edge0, f32 const edge1, f32 x) {
        x = clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
        return x * x * x * ((6.0f * x - 15.0f) * x + 10.0f);
    }

    u8 popcount(u8 v) {
        v = (v & 0x55) + ((v >> 1) & 0x55);
        v = (v & 0x33) + ((v >> 2) & 0x33);
        v = (v & 0x0F) + ((v >> 4) & 0x0F);
        return v;
    }

    u16 popcount(u16 v) {
        v = (v & 0x5555) + ((v >> 1) & 0x5555);
        v = (v & 0x3333) + ((v >> 2) & 0x3333);
        v = (v & 0x0F0F) + ((v >> 4) & 0x0F0F);
        return v * 0x0101 >> 8;
    }

    u32 popcount(u32 v) {
        v = (v & 0x55555555) + ((v >> 1) & 0x55555555);
        v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
        v = (v & 0x0F0F0F0F) + ((v >> 4) & 0x0F0F0F0F);
        return v * 0x01010101 >> 24;
    }

    u64 popcount(u64 v) {
        v = (v & 0x5555555555555555) + ((v >> 1) & 0x5555555555555555);
        v = (v & 0x3333333333333333) + ((v >> 2) & 0x3333333333333333);
        v = (v & 0x0F0F0F0F0F0F0F0F) + ((v >> 4) & 0x0F0F0F0F0F0F0F0F);
        return v * 0x0101010101010101 >> 56;
    }

    u8 clz(u8 v) {
        v |= (v >> 1);
        v |= (v >> 2);
        v |= (v >> 4);
        return 8 - popcount(v);
    }

    u16 clz(u16 v) {
        v |= (v >> 1);
        v |= (v >> 2);
        v |= (v >> 4);
        v |= (v >> 8);
        return 16 - popcount(v);
    }

    u32 clz(u32 v) {
        v |= (v >> 1);
        v |= (v >> 2);
        v |= (v >> 4);
        v |= (v >> 8);
        v |= (v >> 16);
        return 32 - popcount(v);
    }

    u64 clz(u64 v) {
        v |= (v >> 1);
        v |= (v >> 2);
        v |= (v >> 4);
        v |= (v >> 8);
        v |= (v >> 16);
        v |= (v >> 32);
        return 64 - popcount(v);
    }
} // namespace anton::math
