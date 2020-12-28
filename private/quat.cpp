#include <anton/math/quat.hpp>
#include <anton/math/vec4.hpp>
#include <detail/utility.hpp>

namespace anton::math {
    Quat const Quat::identity = Quat(0, 0, 0, 1);

    Quat Quat::from_axis_angle(Vec3 const axis, f32 const angle) {
        f32 const sin = math::sin(angle * 0.5f);
        f32 const cos = math::cos(angle * 0.5f);
        return {axis.x * sin, axis.y * sin, axis.z * sin, cos};
    }

    Quat::Quat(f32 x, f32 y, f32 z, f32 w) : x(x), y(y), z(z), w(w) {}

    f32* Quat::data()  {
        return &x;
    }

    f32 const* Quat::data() const {
        return &x;
    }

    Quat operator+(Quat const& q1, Quat const& q2) {
        return {q1.x + q2.x, q1.y + q2.y, q1.z + q2.z, q1.w + q2.w};
    }

    Quat operator-(Quat const& q1, Quat const& q2) {
        return {q1.x - q2.x, q1.y - q2.y, q1.z - q2.z, q1.w - q2.w};
    }

    Quat operator*(Quat const& p, Quat const& q) {
        return {p.w * q.x + q.w * p.x + p.y * q.z - p.z * q.y,
                p.w * q.y + q.w * p.y + p.z * q.x - p.x * q.z,
                p.w * q.z + q.w * p.z + p.x * q.y - p.y * q.x,
                p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z};
    }

    Quat operator*(Quat const& q, f32 a) {
        return {q.x * a, q.y * a, q.z * a, q.w * a};
    }

    Quat operator/(Quat const& q, f32 a) {
        return {q.x / a, q.y / a, q.z / a, q.w / a};
    }

    f32 length_squared(Quat const& q) {
        return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
    }

    f32 length(Quat const& q) {
        return sqrt(length_squared(q));
    }

    Quat normalize(Quat const& q) {
        return q * math::inv_sqrt(length_squared(q));
    }

    Quat conjugate(Quat const& q) {
        return {-q.x, -q.y, -q.z, q.w};
    }

    Quat inverse(Quat const& q) {
        return conjugate(q) / length_squared(q);
    }

    Quat orient_towards(Vec3 const start, Vec3 const target) {
        f32 const angle_cos = clamp(dot(start, target), -1.0f, 1.0f);
        f32 const angle = acos(angle_cos);
        Vec3 const axis = normalize(cross(start, target));
        if(!is_almost_zero(axis)) {
            return Quat::from_axis_angle(axis, angle);
        } else {
            return Quat::identity;
        }
    }

    Quat slerp(Quat const& a, Quat const& b, f32 const t) {
        Vec4 const v0{a.x, a.y, a.z, a.w};
        Vec4 const v1{b.x, b.y, b.z, b.w};
        f32 const angle_cos = clamp(dot(v0, v1), -1.0f, 1.0f);
        // We use small angle approximation for sin when the angle is < 0.1 radians
        if(angle_cos < 0.995f) {
            f32 const angle = acos(angle_cos);
            f32 const inv_sin_angle = 1.0f / sin(angle);
            f32 const f0 = inv_sin_angle * sin((1.0f - t) * angle);
            f32 const f1 = inv_sin_angle * sin(t * angle);
            Vec4 const r = f0 * v0 + f1 * v1;
            return {r.x, r.y, r.z, r.w};
        } else {
            Vec4 const r = (1.0f - t) * v0 + t * v1;
            return {r.x, r.y, r.z, r.w};
        }
    }

    void swap(Quat& q1, Quat& q2) {
        detail::swap(q1.x, q2.x);
        detail::swap(q1.y, q2.y);
        detail::swap(q1.z, q2.z);
        detail::swap(q1.w, q2.w);
    }
}
