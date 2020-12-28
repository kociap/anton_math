#pragma once

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

        Vec2();
        explicit Vec2(f32 v);
        Vec2(f32 x, f32 y);
        explicit Vec2(Vec3 const& vec3);
        explicit Vec2(Vec4 const& vec4);
        explicit Vec2(f32 const* p);

        [[nodiscard]] f32& operator[](i32 index);
        [[nodiscard]] f32 const& operator[](i32 index) const;

        [[nodiscard]] f32* data();
        [[nodiscard]] f32 const* data() const;
    };

    [[nodiscard]] Vec2 operator-(Vec2 const& v);
    Vec2& operator+=(Vec2& v, Vec2 const& a);
    Vec2& operator-=(Vec2& v, Vec2 const& a);
    Vec2& operator+=(Vec2& v, f32 a);

    // Componentwise multiply.
    //
    Vec2& operator*=(Vec2& v, Vec2 const& a);

    // Componentwise divide.
    //
    Vec2& operator/=(Vec2& v, Vec2 const& a);

    Vec2& operator-=(Vec2& v, f32 a);
    Vec2& operator*=(Vec2& v, f32 a);
    Vec2& operator/=(Vec2& v, f32 a);
    [[nodiscard]] Vec2 operator+(Vec2 const& a, Vec2 const& b);
    [[nodiscard]] Vec2 operator-(Vec2 const& a, Vec2 const& b);

    // Componentwise multiply.
    //
    [[nodiscard]] Vec2 operator*(Vec2 const& a, Vec2 const& b);

    // Componentwise divide.
    //
    [[nodiscard]] Vec2 operator/(Vec2 const& a, Vec2 const& b);

    [[nodiscard]] Vec2 operator+(Vec2 const& a, f32 b);
    [[nodiscard]] Vec2 operator-(Vec2 const& a, f32 b);
    [[nodiscard]] Vec2 operator*(Vec2 const& a, f32 b);
    [[nodiscard]] Vec2 operator*(f32 b, Vec2 const& a);
    [[nodiscard]] Vec2 operator/(Vec2 const& a, f32 b);
    [[nodiscard]] bool operator==(Vec2 const& a, Vec2 const& b);
    [[nodiscard]] bool operator!=(Vec2 const& a, Vec2 const& b);
    [[nodiscard]] bool is_almost_zero(Vec2 const& v, f32 tolerance = 0.000001f);
    [[nodiscard]] f32 dot(Vec2 const& vec1, Vec2 const& vec2);
    [[nodiscard]] f32 length_squared(Vec2 const& v);
    [[nodiscard]] f32 length(Vec2 const& v);

    // normalize
    // If vec is non-zero, returns normalized copy of the vec.
    // Otherwise returns zero vec.
    [[nodiscard]] Vec2 normalize(Vec2 vec, f32 tolerance = 0.000001f);

    // lerp
    // Computes the linear interpolation between a and b for the parameter t in the interval [0, 1].
    //
    [[nodiscard]] Vec2 lerp(Vec2 const& a, Vec2 const& b, f32 const t);

    // slerp
    // Computes the spherical interpolation between a and b for the parameter t in the interval [0, 1].
    // Both vectors a and b must be non-zero.
    //
    [[nodiscard]] Vec2 slerp(Vec2 const& a, Vec2 const& b, f32 t);

    void swap(Vec2& a, Vec2& b);
} // namespace anton::math
