#ifndef ANTON_MATH_VECTOR4_HPP_INCLUDE
#define ANTON_MATH_VECTOR4_HPP_INCLUDE

#include <anton/math/math.hpp>
#include <anton/math/detail/utility.hpp>

namespace anton::math {
    class Vector2;
    class Vector3;

    class Vector4 {
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

        union {
            f32 w;
            f32 a;
        };

        constexpr Vector4(): x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
        constexpr Vector4(f32 v): x(v), y(v), z(v), w(v) {}
        constexpr Vector4(f32 x, f32 y, f32 z, f32 w): x(x), y(y), z(z), w(w) {}
        explicit Vector4(Vector2 const&, f32 z = 0.0f, f32 w = 0.0f);
        explicit Vector4(Vector3 const&, f32 w = 0.0f);

        constexpr f32& operator[](i32 index) {
            return (&x)[index];
        }

        constexpr f32 operator[](i32 index) const {
            return (&x)[index];
        }
    };

    constexpr Vector4 operator-(Vector4 const& v) {
        return {-v.x, -v.y, -v.z, -v.w};
    }

    constexpr Vector4& operator+=(Vector4& v, Vector4 a) {
        v.x += a.x;
        v.y += a.y;
        v.z += a.z;
        v.w += a.w;
        return v;
    }

    constexpr Vector4& operator-=(Vector4& v, Vector4 a) {
        v.x -= a.x;
        v.y -= a.y;
        v.z -= a.z;
        v.w -= a.w;
        return v;
    }

    // Componentwise multiply.
    //
    constexpr Vector4& operator*=(Vector4& v, Vector4 a) {
        v.x *= a.x;
        v.y *= a.y;
        v.z *= a.z;
        v.w *= a.w;
        return v;
    }

    // Componentwise divide.
    //
    constexpr Vector4& operator/=(Vector4& v, Vector4 a) {
        v.x /= a.x;
        v.y /= a.y;
        v.z /= a.z;
        v.w /= a.w;
        return v;
    }

    constexpr Vector4& operator+=(Vector4& v, f32 a) {
        v.x += a;
        v.y += a;
        v.z += a;
        v.w += a;
        return v;
    }

    constexpr Vector4& operator-=(Vector4& v, f32 a) {
        v.x -= a;
        v.y -= a;
        v.z -= a;
        v.w -= a;
        return v;
    }

    constexpr Vector4& operator*=(Vector4& v, f32 a) {
        v.x *= a;
        v.y *= a;
        v.z *= a;
        v.w *= a;
        return v;
    }

    constexpr Vector4& operator/=(Vector4& v, f32 a) {
        v.x /= a;
        v.y /= a;
        v.z /= a;
        v.w /= a;
        return v;
    }

    constexpr Vector4 operator+(Vector4 a, Vector4 b) {
        a += b;
        return a;
    }

    constexpr Vector4 operator-(Vector4 a, Vector4 b) {
        a -= b;
        return a;
    }

    // Componentwise multiply.
    //
    constexpr Vector4 operator*(Vector4 a, Vector4 b) {
        return {a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
    }

    // Componentwise divide.
    //
    constexpr Vector4 operator/(Vector4 a, Vector4 b) {
        return {a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w};
    }

    constexpr Vector4 operator+(Vector4 a, f32 b) {
        a += b;
        return a;
    }

    constexpr Vector4 operator-(Vector4 a, f32 b) {
        a -= b;
        return a;
    }

    constexpr Vector4 operator*(Vector4 a, f32 b) {
        a *= b;
        return a;
    }

    constexpr Vector4 operator*(f32 b, Vector4 a) {
        a *= b;
        return a;
    }

    constexpr Vector4 operator/(Vector4 a, f32 b) {
        a /= b;
        return a;
    }

    constexpr bool operator==(Vector4 a, Vector4 b) {
        return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
    }

    constexpr bool operator!=(Vector4 a, Vector4 b) {
        return a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w;
    }

    constexpr bool is_almost_zero(Vector4 const v, f32 const tolerance = 0.000001f) {
        return math::abs(v.x) <= tolerance && math::abs(v.y) <= tolerance && math::abs(v.z) <= tolerance && math::abs(v.w) <= tolerance;
    }

    constexpr f32 dot(Vector4 const v1, Vector4 const v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
    }

    constexpr f32 length_squared(Vector4 const v) {
        return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
    }

    inline f32 length(Vector4 const v) {
        return math::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    }

    // If vector is non-zero, returns normalized copy of the vector.
    // Otherwise returns zero vector.
    inline Vector4 normalize(Vector4 vec) {
        if (!is_almost_zero(vec)) {
            f32 inverse_vec_length = math::inv_sqrt(length_squared(vec));
            vec *= inverse_vec_length;
        }

        return vec;
    }

    constexpr Vector4 lerp(Vector4 const a, Vector4 const b, f32 const t) {
        return (1.0f - t) * a + t * b;
    }
    
    constexpr void swap(Vector4& a, Vector4& b) {
        detail::swap(a.x, b.x);
        detail::swap(a.y, b.y);
        detail::swap(a.z, b.z);
        detail::swap(a.w, b.w);
    }
} // namespace anton::math

#endif // !ANTON_MATH_VECTOR4_HPP_INCLUDE
