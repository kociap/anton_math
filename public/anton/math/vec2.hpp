#pragma once

#include <anton/math/detail/utility.hpp>
#include <anton/math/math.hpp>

namespace anton::math {
    struct Vec3;
    struct Vec4;

    struct Vec2 {
        union {
            f32 x;
            f32 r;
        };

        union {
            f32 y;
            f32 g;
        };

        constexpr Vec2(): x(0.0f), y(0.0f) {}
        explicit constexpr Vec2(f32 v): x(v), y(v) {}
        constexpr Vec2(f32 x, f32 y): x(x), y(y) {}
        explicit Vec2(Vec3 const& vec3);
        explicit Vec2(Vec4 const& vec4);
        explicit Vec2(f32 const* const p): x(p[0]), y(p[1]) {}

        [[nodiscard]] constexpr f32& operator[](i32 index) {
            return (&x)[index];
        }

        [[nodiscard]] constexpr f32 const& operator[](i32 index) const {
            return (&x)[index];
        }

        [[nodiscard]] f32* data() {
            return &x;
        }

        [[nodiscard]] f32 const* data() const {
            return &x;
        }
    };

    [[nodiscard]] constexpr Vec2 operator-(Vec2 const& v) {
        return {-v.x, -v.y};
    }

    [[nodiscard]] constexpr Vec2& operator+=(Vec2& v, Vec2 a) {
        v.x += a.x;
        v.y += a.y;
        return v;
    }

    [[nodiscard]] constexpr Vec2& operator-=(Vec2& v, Vec2 a) {
        v.x -= a.x;
        v.y -= a.y;
        return v;
    }

    [[nodiscard]] constexpr Vec2& operator+=(Vec2& v, f32 a) {
        v.x += a;
        v.y += a;
        return v;
    }

    // Componentwise multiply.
    //
    [[nodiscard]] constexpr Vec2& operator*=(Vec2& v, Vec2 a) {
        v.x *= a.x;
        v.y *= a.y;
        return v;
    }

    // Componentwise divide.
    //
    [[nodiscard]] constexpr Vec2& operator/=(Vec2& v, Vec2 a) {
        v.x /= a.x;
        v.y /= a.y;
        return v;
    }

    [[nodiscard]] constexpr Vec2& operator-=(Vec2& v, f32 a) {
        v.x -= a;
        v.y -= a;
        return v;
    }

    [[nodiscard]] constexpr Vec2& operator*=(Vec2& v, f32 a) {
        v.x *= a;
        v.y *= a;
        return v;
    }

    [[nodiscard]] constexpr Vec2& operator/=(Vec2& v, f32 a) {
        v.x /= a;
        v.y /= a;
        return v;
    }

    [[nodiscard]] constexpr Vec2 operator+(Vec2 a, Vec2 b) {
        a += b;
        return a;
    }

    [[nodiscard]] constexpr Vec2 operator-(Vec2 a, Vec2 b) {
        a -= b;
        return a;
    }

    // Componentwise multiply.
    //
    [[nodiscard]] constexpr Vec2 operator*(Vec2 a, Vec2 b) {
        return {a.x * b.x, a.y * b.y};
    }

    // Componentwise divide.
    //
    [[nodiscard]] constexpr Vec2 operator/(Vec2 a, Vec2 b) {
        return {a.x / b.x, a.y / b.y};
    }

    [[nodiscard]] constexpr Vec2 operator+(Vec2 a, f32 b) {
        a += b;
        return a;
    }

    [[nodiscard]] constexpr Vec2 operator-(Vec2 a, f32 b) {
        a -= b;
        return a;
    }

    [[nodiscard]] constexpr Vec2 operator*(Vec2 a, f32 b) {
        a *= b;
        return a;
    }

    [[nodiscard]] constexpr Vec2 operator*(f32 b, Vec2 a) {
        a *= b;
        return a;
    }

    [[nodiscard]] constexpr Vec2 operator/(Vec2 a, f32 b) {
        a /= b;
        return a;
    }

    [[nodiscard]] constexpr bool operator==(Vec2 a, Vec2 b) {
        return a.x == b.x && a.y == b.y;
    }

    [[nodiscard]] constexpr bool operator!=(Vec2 a, Vec2 b) {
        return a.x != b.x || a.y != b.y;
    }

    [[nodiscard]] constexpr bool is_almost_zero(Vec2 const v, f32 const tolerance = 0.000001f) {
        return math::abs(v.x) <= tolerance && math::abs(v.y) <= tolerance;
    }

    [[nodiscard]] constexpr f32 dot(Vec2 const vec1, Vec2 const vec2) {
        return vec1.x * vec2.x + vec1.y * vec2.y;
    }

    [[nodiscard]] constexpr f32 length_squared(Vec2 const v) {
        return v.x * v.x + v.y * v.y;
    }

    [[nodiscard]] inline f32 length(Vec2 const v) {
        return math::sqrt(v.x * v.x + v.y * v.y);
    }

    // normalize
    // If vec is non-zero, returns normalized copy of the vec.
    // Otherwise returns zero vec.
    [[nodiscard]] inline Vec2 normalize(Vec2 vec, f32 const tolerance = 0.000001f) {
        if(!is_almost_zero(vec, tolerance)) {
            f32 const inverse_vec_length = math::inv_sqrt(length_squared(vec));
            return vec * inverse_vec_length;
        } else {
            return Vec2{};
        }
    }

    [[nodiscard]] constexpr Vec2 lerp(Vec2 const a, Vec2 const b, f32 const t) {
        return (1.0f - t) * a + t * b;
    }

    constexpr void swap(Vec2& a, Vec2& b) {
        detail::swap(a.x, b.x);
        detail::swap(a.y, b.y);
    }
} // namespace anton::math
