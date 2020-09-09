#pragma once

#include <anton/math/detail/utility.hpp>
#include <anton/math/math.hpp>

namespace anton::math {
    struct Vec2;
    struct Vec4;

    struct Vec3 {
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

        constexpr Vec3(): x(0.0f), y(0.0f), z(0.0f) {}
        explicit constexpr Vec3(f32 v): x(v), y(v), z(v) {}
        constexpr Vec3(f32 x, f32 y, f32 z): x(x), y(y), z(z) {}
        explicit Vec3(Vec2 const& vec2, f32 z = 0.0f);
        explicit Vec3(Vec4 const& vec4);
        explicit Vec3(f32 const* const p): x(p[0]), y(p[1]), z(p[2]) {}

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

    constexpr Vec3 operator-(Vec3 const& v) {
        return {-v.x, -v.y, -v.z};
    }

    constexpr Vec3& operator+=(Vec3& v, Vec3 a) {
        v.x += a.x;
        v.y += a.y;
        v.z += a.z;
        return v;
    }

    constexpr Vec3& operator-=(Vec3& v, Vec3 a) {
        v.x -= a.x;
        v.y -= a.y;
        v.z -= a.z;
        return v;
    }

    // Componentwise multiply.
    //
    constexpr Vec3& operator*=(Vec3& v, Vec3 a) {
        v.x *= a.x;
        v.y *= a.y;
        v.z *= a.z;
        return v;
    }

    constexpr Vec3& operator/=(Vec3& v, Vec3 a) {
        v.x /= a.x;
        v.y /= a.y;
        v.z /= a.z;
        return v;
    }

    constexpr Vec3& operator+=(Vec3& v, f32 a) {
        v.x += a;
        v.y += a;
        v.z += a;
        return v;
    }

    constexpr Vec3& operator-=(Vec3& v, f32 a) {
        v.x -= a;
        v.y -= a;
        v.z -= a;
        return v;
    }

    constexpr Vec3& operator*=(Vec3& v, f32 a) {
        v.x *= a;
        v.y *= a;
        v.z *= a;
        return v;
    }

    constexpr Vec3& operator/=(Vec3& v, f32 a) {
        v.x /= a;
        v.y /= a;
        v.z /= a;
        return v;
    }

    constexpr Vec3 operator+(Vec3 a, Vec3 b) {
        a += b;
        return a;
    }

    constexpr Vec3 operator-(Vec3 a, Vec3 b) {
        a -= b;
        return a;
    }

    // Componentwise multiply.
    //
    constexpr Vec3 operator*(Vec3 a, Vec3 b) {
        return {a.x * b.x, a.y * b.y, a.z * b.z};
    }

    constexpr Vec3 operator/(Vec3 a, Vec3 b) {
        return {a.x / b.x, a.y / b.y, a.z / b.z};
    }

    constexpr Vec3 operator+(Vec3 a, f32 b) {
        a += b;
        return a;
    }

    constexpr Vec3 operator-(Vec3 a, f32 b) {
        a -= b;
        return a;
    }

    constexpr Vec3 operator*(Vec3 a, f32 b) {
        a *= b;
        return a;
    }

    constexpr Vec3 operator*(f32 b, Vec3 a) {
        a *= b;
        return a;
    }

    constexpr Vec3 operator/(Vec3 a, f32 b) {
        a /= b;
        return a;
    }

    constexpr bool operator==(Vec3 a, Vec3 b) {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }

    constexpr bool operator!=(Vec3 a, Vec3 b) {
        return a.x != b.x || a.y != b.y || a.z != b.z;
    }

    constexpr bool is_almost_zero(Vec3 const v, f32 const tolerance = 0.000001f) {
        return math::abs(v.x) <= tolerance && math::abs(v.y) <= tolerance && math::abs(v.z) <= tolerance;
    }

    constexpr f32 dot(Vec3 const v1, Vec3 const v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    constexpr Vec3 cross(Vec3 const v1, Vec3 const v2) {
        return Vec3(v1.y * v2.z - v2.y * v1.z, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
    }

    constexpr f32 length_squared(Vec3 const v) {
        return v.x * v.x + v.y * v.y + v.z * v.z;
    }

    inline f32 length(Vec3 v) {
        return math::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    // normalize
    // If vec is non-zero with given tolerance, returns normalized copy of the vec.
    // Otherwise returns zero vec.
    //
    inline Vec3 normalize(Vec3 vec, f32 const tolerance = 0.000001f) {
        if(!is_almost_zero(vec, tolerance)) {
            f32 const inverse_vec_length = math::inv_sqrt(length_squared(vec));
            return vec * inverse_vec_length;
        } else {
            return Vec3{};
        }
    }

    constexpr Vec3 lerp(Vec3 const a, Vec3 const b, f32 const t) {
        return (1.0f - t) * a + t * b;
    }

    constexpr void swap(Vec3& a, Vec3& b) {
        detail::swap(a.x, b.x);
        detail::swap(a.y, b.y);
        detail::swap(a.z, b.z);
    }
} // namespace anton::math
