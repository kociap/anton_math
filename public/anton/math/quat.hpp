#pragma once


#include <anton/math/math.hpp>
#include <anton/math/vec3.hpp>

namespace anton::math {
    struct Quat {
        // Identity quat.
        // Equivalent to Quat(0, 0, 0, 1)
        static Quat const identity;

        // from_axis_angle
        // Constructs Quat from given axis and angle.
        //
        // axis - normalized axis of rotation.
        // angle - angle of rotation in radians.
        //
        [[nodiscard]] static Quat from_axis_angle(Vec3 const axis, f32 const angle);

        f32 x = 0;
        f32 y = 0;
        f32 z = 0;
        f32 w = 1;

        Quat() = default;
        Quat(f32 x, f32 y, f32 z, f32 w);

        [[nodiscard]] f32* data();
        [[nodiscard]] f32 const* data() const;
    };

    [[nodiscard]] Quat operator-(Quat const& q);
    [[nodiscard]] Quat operator+(Quat const& q1, Quat const& q2);
    [[nodiscard]] Quat operator-(Quat const& q1, Quat const& q2);

    // Hamilton Product
    //
    [[nodiscard]] Quat operator*(Quat const& p, Quat const& q);

    [[nodiscard]] Quat operator*(Quat const& q, f32 a);
    [[nodiscard]] Quat operator/(Quat const& q, f32 a);
    [[nodiscard]] f32 length_squared(Quat const& q);
    [[nodiscard]] f32 length(Quat const& q);
    [[nodiscard]] Quat normalize(Quat const& q);
    [[nodiscard]] Quat conjugate(Quat const& q);

    // inverse
    // Calculates the multiplicative inverse of q. q must be non-zero.
    // If q is normalized, this function returns the same result as conjugate.
    //
    [[nodiscard]] Quat inverse(Quat const& q);

    // orient_towards
    // Constructs a unit quaternion that orients an object towards target from 
    // its inital orientation towards start.
    // start and target must be unit vectors.
    //
    [[nodiscard]] Quat orient_towards(Vec3 const start, Vec3 const target);

    // slerp
    // Computes the spherical interpolation between a and b for the parameter t in the interval [0, 1].
    // Both a and b must be unit quaternions.
    //
    [[nodiscard]] Quat slerp(Quat const& a, Quat const& b, f32 t);

    void swap(Quat& q1, Quat& q2);
} // namespace anton::math
