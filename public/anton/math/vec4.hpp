#pragma once

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

        Vec4();
        explicit Vec4(f32 v);
        Vec4(f32 x, f32 y, f32 z, f32 w);
        explicit Vec4(Vec2 const& vec2, f32 z = 0.0f, f32 w = 0.0f);
        explicit Vec4(Vec3 const& vec3, f32 w = 0.0f);
        explicit Vec4(f32 const* const p);

        [[nodiscard]] f32& operator[](i32 index);
        [[nodiscard]] f32 const& operator[](i32 index) const;

        [[nodiscard]] f32* data();
        [[nodiscard]] f32 const* data() const;
    };

    [[nodiscard]] Vec4 operator-(Vec4 const& v);
    Vec4& operator+=(Vec4& v, Vec4 const& a);
    Vec4& operator-=(Vec4& v, Vec4 const& a);

    // Componentwise multiply.
    //
    Vec4& operator*=(Vec4& v, Vec4 const& a);

    // Componentwise divide.
    //
    Vec4& operator/=(Vec4& v, Vec4 const& a);

    Vec4& operator+=(Vec4& v, f32 a);
    Vec4& operator-=(Vec4& v, f32 a);
    Vec4& operator*=(Vec4& v, f32 a);
    Vec4& operator/=(Vec4& v, f32 a);

    [[nodiscard]] Vec4 operator+(Vec4 const& a, Vec4 const& b);
    [[nodiscard]] Vec4 operator-(Vec4 const& a, Vec4 const& b);

    // Componentwise multiply.
    //
    [[nodiscard]] Vec4 operator*(Vec4 const& a, Vec4 const& b);

    // Componentwise divide.
    //
    [[nodiscard]] Vec4 operator/(Vec4 const& a, Vec4 const& b);

    [[nodiscard]] Vec4 operator+(Vec4 const& a, f32 b);
    [[nodiscard]] Vec4 operator-(Vec4 const& a, f32 b);
    [[nodiscard]] Vec4 operator*(Vec4 const& a, f32 b);
    [[nodiscard]] Vec4 operator*(f32 b, Vec4 const& a);
    [[nodiscard]] Vec4 operator/(Vec4 const& a, f32 b);
    [[nodiscard]] bool operator==(Vec4 const& a, Vec4 const& b);
    [[nodiscard]] bool operator!=(Vec4 const& a, Vec4 const& b);
    [[nodiscard]] bool is_almost_zero(Vec4 const& v, f32 tolerance = 0.000001f);
    [[nodiscard]] f32 dot(Vec4 const& v1, Vec4 const& v2);
    [[nodiscard]] f32 length_squared(Vec4 const& v);
    [[nodiscard]] f32 length(Vec4 const& v);

    // normalize
    // If vec is non-zero, returns normalized copy of the vec.
    // Otherwise returns zero vec.
    [[nodiscard]] Vec4 normalize(Vec4 vec, f32 tolerance = 0.000001f);

    // lerp
    // Computes the linear interpolation between a and b for the parameter t in the interval [0, 1].
    //
    [[nodiscard]] Vec4 lerp(Vec4 const& a, Vec4 const& b, f32 t);

    // slerp
    // Computes the spherical interpolation between a and b for the parameter t in the interval [0, 1].
    // Both vectors a and b must be non-zero.
    //
    [[nodiscard]] Vec4 slerp(Vec4 const& a, Vec4 const& b, f32 t);

    void swap(Vec4& a, Vec4& b);
} // namespace anton::math
