#pragma once

#include <anton/math/detail/utility.hpp>
#include <anton/math/math.hpp>

namespace anton::math {
    class Vector2;
    class Vector4;

    class Vector3 {
    public:
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

        constexpr Vector3(): x(0.0f), y(0.0f), z(0.0f) {}
        explicit constexpr Vector3(f32 v): x(v), y(v), z(v) {}
        constexpr Vector3(f32 x, f32 y, f32 z): x(x), y(y), z(z) {}
        explicit Vector3(Vector2 const& vec2, f32 z = 0.0f);
        explicit Vector3(Vector4 const& vec4);
        explicit Vector3(f32 const* const p): x(p[0]), y(p[1]), z(p[2]) {}

        constexpr f32& operator[](i32 index) {
            return (&x)[index];
        }

        constexpr f32 operator[](i32 index) const {
            return (&x)[index];
        }

        f32 const* data() const {
            return &x;
        }
    };

    constexpr Vector3 operator-(Vector3 const& v) {
        return {-v.x, -v.y, -v.z};
    }

    constexpr Vector3& operator+=(Vector3& v, Vector3 a) {
        v.x += a.x;
        v.y += a.y;
        v.z += a.z;
        return v;
    }

    constexpr Vector3& operator-=(Vector3& v, Vector3 a) {
        v.x -= a.x;
        v.y -= a.y;
        v.z -= a.z;
        return v;
    }

    // Componentwise multiply.
    //
    constexpr Vector3& operator*=(Vector3& v, Vector3 a) {
        v.x *= a.x;
        v.y *= a.y;
        v.z *= a.z;
        return v;
    }

    constexpr Vector3& operator/=(Vector3& v, Vector3 a) {
        v.x /= a.x;
        v.y /= a.y;
        v.z /= a.z;
        return v;
    }

    constexpr Vector3& operator+=(Vector3& v, f32 a) {
        v.x += a;
        v.y += a;
        v.z += a;
        return v;
    }

    constexpr Vector3& operator-=(Vector3& v, f32 a) {
        v.x -= a;
        v.y -= a;
        v.z -= a;
        return v;
    }

    constexpr Vector3& operator*=(Vector3& v, f32 a) {
        v.x *= a;
        v.y *= a;
        v.z *= a;
        return v;
    }

    constexpr Vector3& operator/=(Vector3& v, f32 a) {
        v.x /= a;
        v.y /= a;
        v.z /= a;
        return v;
    }

    constexpr Vector3 operator+(Vector3 a, Vector3 b) {
        a += b;
        return a;
    }

    constexpr Vector3 operator-(Vector3 a, Vector3 b) {
        a -= b;
        return a;
    }

    // Componentwise multiply.
    //
    constexpr Vector3 operator*(Vector3 a, Vector3 b) {
        return {a.x * b.x, a.y * b.y, a.z * b.z};
    }

    constexpr Vector3 operator/(Vector3 a, Vector3 b) {
        return {a.x / b.x, a.y / b.y, a.z / b.z};
    }

    constexpr Vector3 operator+(Vector3 a, f32 b) {
        a += b;
        return a;
    }

    constexpr Vector3 operator-(Vector3 a, f32 b) {
        a -= b;
        return a;
    }

    constexpr Vector3 operator*(Vector3 a, f32 b) {
        a *= b;
        return a;
    }

    constexpr Vector3 operator*(f32 b, Vector3 a) {
        a *= b;
        return a;
    }

    constexpr Vector3 operator/(Vector3 a, f32 b) {
        a /= b;
        return a;
    }

    constexpr bool operator==(Vector3 a, Vector3 b) {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }

    constexpr bool operator!=(Vector3 a, Vector3 b) {
        return a.x != b.x || a.y != b.y || a.z != b.z;
    }

    constexpr bool is_almost_zero(Vector3 const v, f32 const tolerance = 0.000001f) {
        return math::abs(v.x) <= tolerance && math::abs(v.y) <= tolerance && math::abs(v.z) <= tolerance;
    }

    constexpr f32 dot(Vector3 const v1, Vector3 const v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    constexpr Vector3 cross(Vector3 const v1, Vector3 const v2) {
        return Vector3(v1.y * v2.z - v2.y * v1.z, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
    }

    constexpr f32 length_squared(Vector3 const v) {
        return v.x * v.x + v.y * v.y + v.z * v.z;
    }

    inline f32 length(Vector3 v) {
        return math::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    // normalize
    // If vector is non-zero with given tolerance, returns normalized copy of the vector.
    // Otherwise returns zero vector.
    //
    inline Vector3 normalize(Vector3 vec, f32 const tolerance = 0.000001f) {
        if(!is_almost_zero(vec, tolerance)) {
            f32 const inverse_vec_length = math::inv_sqrt(length_squared(vec));
            return vec * inverse_vec_length;
        } else {
            return Vector3{};
        }
    }

    constexpr Vector3 lerp(Vector3 const a, Vector3 const b, f32 const t) {
        return (1.0f - t) * a + t * b;
    }

    constexpr void swap(Vector3& a, Vector3& b) {
        detail::swap(a.x, b.x);
        detail::swap(a.y, b.y);
        detail::swap(a.z, b.z);
    }
} // namespace anton::math
