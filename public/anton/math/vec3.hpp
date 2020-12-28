#pragma once

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

        Vec3();
        explicit Vec3(f32 v);
        Vec3(f32 x, f32 y, f32 z);
        explicit Vec3(Vec2 const& vec2, f32 z = 0.0f);
        explicit Vec3(Vec4 const& vec4);
        explicit Vec3(f32 const* const p);

        [[nodiscard]] f32& operator[](i32 index);
        [[nodiscard]] f32 const& operator[](i32 index) const;

        [[nodiscard]] f32* data();
        [[nodiscard]] f32 const* data() const;
    };

    [[nodiscard]] Vec3 operator-(Vec3 const& v);
    Vec3& operator+=(Vec3& v, Vec3 const& a);
    Vec3& operator-=(Vec3& v, Vec3 const& a);

    // Componentwise multiply.
    //
    Vec3& operator*=(Vec3& v, Vec3 const& a);

    // Componentwise divide.
    //
    Vec3& operator/=(Vec3& v, Vec3 const& a);

    Vec3& operator+=(Vec3& v, f32 a);
    Vec3& operator-=(Vec3& v, f32 a);
    Vec3& operator*=(Vec3& v, f32 a);
    Vec3& operator/=(Vec3& v, f32 a);

    [[nodiscard]] Vec3 operator+(Vec3 const& a, Vec3 const& b);
    [[nodiscard]] Vec3 operator-(Vec3 const& a, Vec3 const& b);

    // Componentwise multiply.
    //
    [[nodiscard]] Vec3 operator*(Vec3 const& a, Vec3 const& b);

    // Componentwise divide.
    //
    [[nodiscard]] Vec3 operator/(Vec3 const& a, Vec3 const& b);
    
    [[nodiscard]] Vec3 operator+(Vec3 const& a, f32 b);
    [[nodiscard]] Vec3 operator-(Vec3 const& a, f32 b);
    [[nodiscard]] Vec3 operator*(Vec3 const& a, f32 b);
    [[nodiscard]] Vec3 operator*(f32 b, Vec3 const& a);
    [[nodiscard]] Vec3 operator/(Vec3 const& a, f32 b);
    [[nodiscard]] bool operator==(Vec3 const& a, Vec3 const& b);
    [[nodiscard]] bool operator!=(Vec3 const& a, Vec3 const& b);
    [[nodiscard]] bool is_almost_zero(Vec3 const& v, f32 const tolerance = 0.000001f);
    [[nodiscard]] f32 dot(Vec3 const& v1, Vec3 const& v2);
    [[nodiscard]] Vec3 cross(Vec3 const& v1, Vec3 const& v2);
    [[nodiscard]] f32 length_squared(Vec3 const& v);
    [[nodiscard]] f32 length(Vec3 const& v);

    // normalize
    // If vec is non-zero with given tolerance, returns normalized copy of the vec.
    // Otherwise returns zero vec.
    //
    [[nodiscard]] Vec3 normalize(Vec3 vec, f32 const tolerance = 0.000001f);

    // lerp
    // Computes the linear interpolation between a and b for the parameter t in the interval [0, 1].
    //
    [[nodiscard]] Vec3 lerp(Vec3 const a, Vec3 const b, f32 const t);

    // slerp
    // Computes the spherical interpolation between a and b for the parameter t in the interval [0, 1].
    // Both vectors a and b must be non-zero.
    //
    [[nodiscard]] Vec3 slerp(Vec3 const& a, Vec3 const& b, f32 t);

    void swap(Vec3& a, Vec3& b);
} // namespace anton::math
