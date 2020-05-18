#ifndef ANTON_MATH_VECTOR2_HPP_INLCUDE
#define ANTON_MATH_VECTOR2_HPP_INLCUDE

#include <anton/math/math.hpp>
#include <anton/math/detail/utility.hpp>

namespace anton::math {
    class Vector3;
    class Vector4;

    class Vector2 {
    public:
        union {
            f32 x;
            f32 r;
        };

        union {
            f32 y;
            f32 g;
        };

        constexpr Vector2(): x(0.0f), y(0.0f) {}
        constexpr Vector2(f32 v): x(v), y(v){}
        constexpr Vector2(f32 x, f32 y): x(x), y(y) {}
        explicit Vector2(Vector3 const& vec3);
        explicit Vector2(Vector4 const& vec4);
        explicit Vector2(f32 const* const p): x(p[0]), y(p[1]) {}

        constexpr f32& operator[](i32 index) {
            return (&x)[index];
        }

        constexpr f32 operator[](i32 index) const {
            return (&x)[index];
        }
    };

    constexpr Vector2 operator-(Vector2 const& v) {
        return {-v.x, -v.y};
    }

    constexpr Vector2& operator+=(Vector2& v, Vector2 a) {
        v.x += a.x;
        v.y += a.y;
        return v;
    }

    constexpr Vector2& operator-=(Vector2& v, Vector2 a) {
        v.x -= a.x;
        v.y -= a.y;
        return v;
    }

    constexpr Vector2& operator+=(Vector2& v, f32 a) {
        v.x += a;
        v.y += a;
        return v;
    }

    // Componentwise multiply.
    //
    constexpr Vector2& operator*=(Vector2& v, Vector2 a) {
        v.x *= a.x;
        v.y *= a.y;
        return v;
    }

    // Componentwise divide.
    //
    constexpr Vector2& operator/=(Vector2& v, Vector2 a) {
        v.x /= a.x;
        v.y /= a.y;
        return v;
    }

    constexpr Vector2& operator-=(Vector2& v, f32 a) {
        v.x -= a;
        v.y -= a;
        return v;
    }

    constexpr Vector2& operator*=(Vector2& v, f32 a) {
        v.x *= a;
        v.y *= a;
        return v;
    }

    constexpr Vector2& operator/=(Vector2& v, f32 a) {
        v.x /= a;
        v.y /= a;
        return v;
    }

    constexpr Vector2 operator+(Vector2 a, Vector2 b) {
        a += b;
        return a;
    }

    constexpr Vector2 operator-(Vector2 a, Vector2 b) {
        a -= b;
        return a;
    }

    // Componentwise multiply.
    //
    constexpr Vector2 operator*(Vector2 a, Vector2 b) {
        return {a.x * b.x, a.y * b.y};
    }

    // Componentwise divide.
    //
    constexpr Vector2 operator/(Vector2 a, Vector2 b) {
        return {a.x / b.x, a.y / b.y};
    }

    constexpr Vector2 operator+(Vector2 a, f32 b) {
        a += b;
        return a;
    }

    constexpr Vector2 operator-(Vector2 a, f32 b) {
        a -= b;
        return a;
    }

    constexpr Vector2 operator*(Vector2 a, f32 b) {
        a *= b;
        return a;
    }

    constexpr Vector2 operator*(f32 b, Vector2 a) {
        a *= b;
        return a;
    }

    constexpr Vector2 operator/(Vector2 a, f32 b) {
        a /= b;
        return a;
    }

    constexpr bool operator==(Vector2 a, Vector2 b) {
        return a.x == b.x && a.y == b.y;
    }

    constexpr bool operator!=(Vector2 a, Vector2 b) {
        return a.x != b.x || a.y != b.y;
    }

    constexpr bool is_almost_zero(Vector2 const v, f32 const tolerance = 0.000001f) {
        return math::abs(v.x) <= tolerance && math::abs(v.y) <= tolerance;
    }

    constexpr f32 dot(Vector2 const vec1, Vector2 const vec2) {
        return vec1.x * vec2.x + vec1.y * vec2.y;
    }

    constexpr f32 length_squared(Vector2 const v) {
        return v.x * v.x + v.y * v.y;
    }

    inline f32 length(Vector2 const v) {
        return math::sqrt(v.x * v.x + v.y * v.y);
    }

    // If vector is non-zero, returns normalized copy of the vector.
    // Otherwise returns zero vector.
    inline Vector2 normalize(Vector2 vec) {
        if (!is_almost_zero(vec)) {
            f32 inverse_vec_length = math::inv_sqrt(math::length_squared(vec));
            vec *= inverse_vec_length;
        }

        return vec;
    }

    constexpr Vector2 lerp(Vector2 const a, Vector2 const b, f32 const t) {
        return (1.0f - t) * a + t * b;
    }
    
    constexpr void swap(Vector2& a, Vector2& b) {
        detail::swap(a.x, b.x);
        detail::swap(a.y, b.y);
    }
} // namespace anton::math

#endif // !ANTON_MATH_VECTOR2_HPP_INLCUDE
