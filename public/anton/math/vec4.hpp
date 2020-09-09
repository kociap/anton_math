#pragma once

#include <anton/math/detail/utility.hpp>
#include <anton/math/math.hpp>

namespace anton::math {
    struct Vec2;
    struct Vec3;

    struct Vec4 {
        union {
            f32 x;
            f32 r;
        };

        union {
            f32 y;
            f32 g;
        };

        union {
            f32 z;
            f32 b;
        };

        union {
            f32 w;
            f32 a;
        };

        constexpr Vec4(): x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
        explicit constexpr Vec4(f32 v): x(v), y(v), z(v), w(v) {}
        constexpr Vec4(f32 x, f32 y, f32 z, f32 w): x(x), y(y), z(z), w(w) {}
        explicit Vec4(Vec2 const& vec2, f32 z = 0.0f, f32 w = 0.0f);
        explicit Vec4(Vec3 const& vec3, f32 w = 0.0f);
        explicit Vec4(f32 const* const p): x(p[0]), y(p[1]), z(p[2]), w(p[3]) {}

        constexpr f32& operator[](i32 index) {
            return (&x)[index];
        }

        constexpr f32 operator[](i32 index) const {
            return (&x)[index];
        }

        f32* data() {
            return &x;
        }

        f32 const* data() const {
            return &x;
        }
    };

    constexpr Vec4 operator-(Vec4 const& v) {
        return {-v.x, -v.y, -v.z, -v.w};
    }

    constexpr Vec4& operator+=(Vec4& v, Vec4 a) {
        v.x += a.x;
        v.y += a.y;
        v.z += a.z;
        v.w += a.w;
        return v;
    }

    constexpr Vec4& operator-=(Vec4& v, Vec4 a) {
        v.x -= a.x;
        v.y -= a.y;
        v.z -= a.z;
        v.w -= a.w;
        return v;
    }

    // Componentwise multiply.
    //
    constexpr Vec4& operator*=(Vec4& v, Vec4 a) {
        v.x *= a.x;
        v.y *= a.y;
        v.z *= a.z;
        v.w *= a.w;
        return v;
    }

    // Componentwise divide.
    //
    constexpr Vec4& operator/=(Vec4& v, Vec4 a) {
        v.x /= a.x;
        v.y /= a.y;
        v.z /= a.z;
        v.w /= a.w;
        return v;
    }

    constexpr Vec4& operator+=(Vec4& v, f32 a) {
        v.x += a;
        v.y += a;
        v.z += a;
        v.w += a;
        return v;
    }

    constexpr Vec4& operator-=(Vec4& v, f32 a) {
        v.x -= a;
        v.y -= a;
        v.z -= a;
        v.w -= a;
        return v;
    }

    constexpr Vec4& operator*=(Vec4& v, f32 a) {
        v.x *= a;
        v.y *= a;
        v.z *= a;
        v.w *= a;
        return v;
    }

    constexpr Vec4& operator/=(Vec4& v, f32 a) {
        v.x /= a;
        v.y /= a;
        v.z /= a;
        v.w /= a;
        return v;
    }

    constexpr Vec4 operator+(Vec4 a, Vec4 b) {
        a += b;
        return a;
    }

    constexpr Vec4 operator-(Vec4 a, Vec4 b) {
        a -= b;
        return a;
    }

    // Componentwise multiply.
    //
    constexpr Vec4 operator*(Vec4 a, Vec4 b) {
        return {a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
    }

    // Componentwise divide.
    //
    constexpr Vec4 operator/(Vec4 a, Vec4 b) {
        return {a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w};
    }

    constexpr Vec4 operator+(Vec4 a, f32 b) {
        a += b;
        return a;
    }

    constexpr Vec4 operator-(Vec4 a, f32 b) {
        a -= b;
        return a;
    }

    constexpr Vec4 operator*(Vec4 a, f32 b) {
        a *= b;
        return a;
    }

    constexpr Vec4 operator*(f32 b, Vec4 a) {
        a *= b;
        return a;
    }

    constexpr Vec4 operator/(Vec4 a, f32 b) {
        a /= b;
        return a;
    }

    constexpr bool operator==(Vec4 a, Vec4 b) {
        return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
    }

    constexpr bool operator!=(Vec4 a, Vec4 b) {
        return a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w;
    }

    constexpr bool is_almost_zero(Vec4 const v, f32 const tolerance = 0.000001f) {
        return math::abs(v.x) <= tolerance && math::abs(v.y) <= tolerance && math::abs(v.z) <= tolerance && math::abs(v.w) <= tolerance;
    }

    constexpr f32 dot(Vec4 const v1, Vec4 const v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
    }

    constexpr f32 length_squared(Vec4 const v) {
        return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
    }

    inline f32 length(Vec4 const v) {
        return math::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    }

    // normalize
    // If vec is non-zero, returns normalized copy of the vec.
    // Otherwise returns zero vec.
    inline Vec4 normalize(Vec4 vec, f32 const tolerance = 0.000001f) {
        if(!is_almost_zero(vec, tolerance)) {
            f32 const inverse_vec_length = math::inv_sqrt(length_squared(vec));
            return vec * inverse_vec_length;
        } else {
            return Vec4{};
        }
    }

    constexpr Vec4 lerp(Vec4 const a, Vec4 const b, f32 const t) {
        return (1.0f - t) * a + t * b;
    }

    constexpr void swap(Vec4& a, Vec4& b) {
        detail::swap(a.x, b.x);
        detail::swap(a.y, b.y);
        detail::swap(a.z, b.z);
        detail::swap(a.w, b.w);
    }
} // namespace anton::math
