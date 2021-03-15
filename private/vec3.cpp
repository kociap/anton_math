#include <anton/math/vec2.hpp>
#include <anton/math/vec3.hpp>
#include <anton/math/vec4.hpp>
#include <anton/math/math.hpp>
#include <detail/utility.hpp>

namespace anton::math {
    Vec3::Vec3(): x(0.0f), y(0.0f), z(0.0f) {}
    Vec3::Vec3(f32 v): x(v), y(v), z(v) {}
    Vec3::Vec3(f32 x, f32 y, f32 z): x(x), y(y), z(z) {}
    Vec3::Vec3(Vec2 const& vec, f32 z /* = 0.0f */): x(vec.x), y(vec.y), z(z) {}
    Vec3::Vec3(Vec4 const& vec): x(vec.x), y(vec.y), z(vec.z) {}
    Vec3::Vec3(f32 const* const p): x(p[0]), y(p[1]), z(p[2]) {}

    f32& Vec3::operator[](i32 index) {
        return (&x)[index];
    }

    f32 const& Vec3::operator[](i32 index) const {
        return (&x)[index];
    }

    f32* Vec3::data() {
        return &x;
    }

    f32 const* Vec3::data() const {
        return &x;
    }
    
    void swap(Vec3& a, Vec3& b) {
        detail::swap(a.x, b.x);
        detail::swap(a.y, b.y);
        detail::swap(a.z, b.z);
    }

    Vec3 operator-(Vec3 const& v) {
        return {-v.x, -v.y, -v.z};
    }

    Vec3& operator+=(Vec3& v, Vec3 const& a) {
        v.x += a.x;
        v.y += a.y;
        v.z += a.z;
        return v;
    }

    Vec3& operator-=(Vec3& v, Vec3 const& a) {
        v.x -= a.x;
        v.y -= a.y;
        v.z -= a.z;
        return v;
    }

    Vec3& operator*=(Vec3& v, Vec3 const& a) {
        v.x *= a.x;
        v.y *= a.y;
        v.z *= a.z;
        return v;
    }

    Vec3& operator/=(Vec3& v, Vec3 const& a) {
        v.x /= a.x;
        v.y /= a.y;
        v.z /= a.z;
        return v;
    }

    Vec3& operator+=(Vec3& v, f32 a) {
        v.x += a;
        v.y += a;
        v.z += a;
        return v;
    }

    Vec3& operator-=(Vec3& v, f32 a) {
        v.x -= a;
        v.y -= a;
        v.z -= a;
        return v;
    }

    Vec3& operator*=(Vec3& v, f32 a) {
        v.x *= a;
        v.y *= a;
        v.z *= a;
        return v;
    }

    Vec3& operator/=(Vec3& v, f32 a) {
        v.x /= a;
        v.y /= a;
        v.z /= a;
        return v;
    }

    Vec3 operator+(Vec3 const& a, Vec3 const& b) {
        return {a.x + b.x, a.y + b.y, a.z + b.z};
    }

    Vec3 operator-(Vec3 const& a, Vec3 const& b) {
        return {a.x - b.x, a.y - b.y, a.z - b.z};
    }

    Vec3 operator*(Vec3 const& a, Vec3 const& b) {
        return {a.x * b.x, a.y * b.y, a.z * b.z};
    }

    Vec3 operator/(Vec3 const& a, Vec3 const& b) {
        return {a.x / b.x, a.y / b.y, a.z / b.z};
    }

    Vec3 operator+(Vec3 const& a, f32 b) {
        return {a.x + b, a.y + b, a.z + b};
    }

    Vec3 operator-(Vec3 const& a, f32 b) {
        return {a.x - b, a.y - b, a.z - b};
    }

    Vec3 operator*(Vec3 const& a, f32 b) {
        return {a.x * b, a.y * b, a.z * b};
    }

    Vec3 operator*(f32 b, Vec3 const& a) {
        return {a.x * b, a.y * b, a.z * b};
    }

    Vec3 operator/(Vec3 const& a, f32 b) {
        return {a.x / b, a.y / b, a.z / b};
    }

    bool operator==(Vec3 const& a, Vec3 const& b) {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }

    bool operator!=(Vec3 const& a, Vec3 const& b) {
        return a.x != b.x || a.y != b.y || a.z != b.z;
    }

    Vec3 max(Vec3 const& v1, Vec3 const& v2) {
        return {v1.x > v2.x ? v1.x : v2.x, v1.y > v2.y ? v1.y : v2.y, v1.z > v2.z ? v1.z : v2.z};
    }

    Vec3 min(Vec3 const& v1, Vec3 const& v2) {
        return {v1.x < v2.x ? v1.x : v2.x, v1.y < v2.y ? v1.y : v2.y, v1.z < v2.z ? v1.z : v2.z};
    }

    bool is_almost_zero(Vec3 const& v, f32 const tolerance /* = 0.000001f */) {
        return math::abs(v.x) <= tolerance && math::abs(v.y) <= tolerance && math::abs(v.z) <= tolerance;
    }

    f32 dot(Vec3 const& v1, Vec3 const& v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    Vec3 cross(Vec3 const& v1, Vec3 const& v2) {
        return Vec3(v1.y * v2.z - v2.y * v1.z, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
    }

    f32 length_squared(Vec3 const& v) {
        return v.x * v.x + v.y * v.y + v.z * v.z;
    }

    f32 length(Vec3 const& v) {
        return math::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    Vec3 normalize(Vec3 vec, f32 const tolerance /* = 0.000001f */) {
        if(!is_almost_zero(vec, tolerance)) {
            f32 const inverse_vec_length = math::inv_sqrt(length_squared(vec));
            return vec * inverse_vec_length;
        } else {
            return Vec3{};
        }
    }

    Vec3 lerp(Vec3 const& a, Vec3 const& b, f32 const t) {
        return (1.0f - t) * a + t * b;
    }

    Vec3 slerp(Vec3 const& a, Vec3 const& b, f32 const t) {
        Vec3 const norm_a = normalize(a);
        Vec3 const norm_b = normalize(b);
        f32 const angle_cos = clamp(dot(norm_a, norm_b), -1.0f, 1.0f);
        // We use small angle approximation for sin when the angle is < 0.1 radians
        if(angle_cos < 0.995f) {
            f32 const angle = acos(angle_cos);
            f32 const inv_sin_angle = 1.0f / sin(angle);
            f32 const f0 = inv_sin_angle * sin((1.0f - t) * angle);
            f32 const f1 = inv_sin_angle * sin(t * angle);
            return f0 * a + f1 * b;
        } else {
            return (1.0f - t) * a + t * b;
        }
    }

    Vec3 perpendicular(Vec3 const& v) {
        if(v.x == 0.0f) {
            return math::normalize(math::Vec3{0.0f, -v.z, v.y});
        } else if(v.y == 0.0f) {
            return math::normalize(math::Vec3{-v.z, 0.0f, v.x});
        } else {
            return math::normalize(math::Vec3{-v.y, v.x, 0.0f});
        }
    }
}
