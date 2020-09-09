#pragma once

#include <anton/math/detail/utility.hpp>
#include <anton/math/math.hpp>
#include <anton/math/vec3.hpp>

namespace anton::math {
    struct Quat {
        // from_axis_angle
        // Constructs quat from given axis and angle.
        //
        // axis - normalized axis of rotation.
        // angle - angle of rotation in radians.
        //
        static Quat from_axis_angle(Vec3 const axis, f32 const angle) {
            f32 const sin = math::sin(angle * 0.5f);
            f32 const cos = math::cos(angle * 0.5f);
            return {axis.x * sin, axis.y * sin, axis.z * sin, cos};
        }

        // Identity quat.
        // Equivalent to Quat(0, 0, 0, 1)
        static Quat const identity;

        f32 x = 0;
        f32 y = 0;
        f32 z = 0;
        f32 w = 1;

        Quat() = default;
        Quat(f32 x, f32 y, f32 z, f32 w) : x(x), y(y), z(z), w(w) {}

        f32* data()  {
            return &x;
        }

        f32 const* data() const {
            return &x;
        }
    };

    inline Quat const Quat::identity = Quat(0, 0, 0, 1);

    inline Quat operator+(Quat const& q1, Quat const& q2) {
        return {q1.x + q2.x, q1.y + q2.y, q1.z + q2.z, q1.w + q2.w};
    }

    inline Quat operator-(Quat const& q1, Quat const& q2) {
        return {q1.x - q2.x, q1.y - q2.y, q1.z - q2.z, q1.w - q2.w};
    }

    // Hamilton Product
    //
    inline Quat operator*(Quat p, Quat q) {
        return {p.w * q.x + q.w * p.x + p.y * q.z - p.z * q.y,
                p.w * q.y + q.w * p.y + p.z * q.x - p.x * q.z,
                p.w * q.z + q.w * p.z + p.x * q.y - p.y * q.x,
                p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z};
    }

    inline Quat operator*(Quat const& q, f32 a) {
        return {q.x * a, q.y * a, q.z * a, q.w * a};
    }

    inline Quat operator/(Quat const& q, f32 a) {
        return {q.x / a, q.y / a, q.z / a, q.w / a};
    }

    inline f32 length_squared(Quat const& q) {
        return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
    }

    inline f32 length(Quat const& q) {
        return sqrt(length_squared(q));
    }

    inline Quat normalize(Quat const& q) {
        return q * math::inv_sqrt(length_squared(q));
    }

    inline Quat conjugate(Quat const& q) {
        return {-q.x, -q.y, -q.z, q.w};
    }

    // inverse
    // If quat is normalized, this function returns the same result as conjugate.
    //
    inline Quat inverse(Quat const& q) {
        return conjugate(q) / length_squared(q);
    }

    // orient_towards
    // Constructs a unit quaternion that orients an object towards target from 
    // its inital orientation towards start.
    // start and target must be unit vectors.
    //
    [[nodiscard]] inline Quat orient_towards(Vec3 const start, Vec3 const target) {
        f32 const angle_cos = dot(start, target);
        f32 const angle = acos(angle_cos);
        Vec3 const axis = normalize(cross(start, target));
        if(!is_almost_zero(axis)) {
            return Quat::from_axis_angle(axis, angle);
        } else {
            return Quat::identity;
        }
    }

    inline void swap(Quat& q1, Quat& q2) {
        detail::swap(q1.x, q2.x);
        detail::swap(q1.y, q2.y);
        detail::swap(q1.z, q2.z);
        detail::swap(q1.w, q2.w);
    }
} // namespace anton::math
