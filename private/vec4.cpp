#include <anton/math/vec2.hpp>
#include <anton/math/vec3.hpp>
#include <anton/math/vec4.hpp>
#include <anton/math/math.hpp>
#include <detail/utility.hpp>

namespace anton::math {
    Vec4::Vec4(): x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    Vec4::Vec4(f32 v): x(v), y(v), z(v), w(v) {}
    Vec4::Vec4(f32 x, f32 y, f32 z, f32 w): x(x), y(y), z(z), w(w) {}
    Vec4::Vec4(Vec2 const& vec, f32 z /* = 0.0f */, f32 w /* = 0.0f */): x(vec.x), y(vec.y), z(z), w(w) {}
    Vec4::Vec4(Vec3 const& vec, f32 w /* = 0.0f */): x(vec.x), y(vec.y), z(vec.z), w(w) {}
    Vec4::Vec4(f32 const* const p): x(p[0]), y(p[1]), z(p[2]), w(p[3]) {}

    f32& Vec4::operator[](i32 index) {
        return (&x)[index];
    }

    f32 const& Vec4::operator[](i32 index) const {
        return (&x)[index];
    }

    f32* Vec4::data() {
        return &x;
    }

    f32 const* Vec4::data() const {
        return &x;
    }

    Vec4 operator-(Vec4 const& v) {
        return {-v.x, -v.y, -v.z, -v.w};
    }

    Vec4& operator+=(Vec4& v, Vec4 const& a) {
        v.x += a.x;
        v.y += a.y;
        v.z += a.z;
        v.w += a.w;
        return v;
    }

    Vec4& operator-=(Vec4& v, Vec4 const& a) {
        v.x -= a.x;
        v.y -= a.y;
        v.z -= a.z;
        v.w -= a.w;
        return v;
    }

    Vec4& operator*=(Vec4& v, Vec4 const& a) {
        v.x *= a.x;
        v.y *= a.y;
        v.z *= a.z;
        v.w *= a.w;
        return v;
    }

    Vec4& operator/=(Vec4& v, Vec4 const& a) {
        v.x /= a.x;
        v.y /= a.y;
        v.z /= a.z;
        v.w /= a.w;
        return v;
    }

    Vec4& operator+=(Vec4& v, f32 a) {
        v.x += a;
        v.y += a;
        v.z += a;
        v.w += a;
        return v;
    }

    Vec4& operator-=(Vec4& v, f32 a) {
        v.x -= a;
        v.y -= a;
        v.z -= a;
        v.w -= a;
        return v;
    }

    Vec4& operator*=(Vec4& v, f32 a) {
        v.x *= a;
        v.y *= a;
        v.z *= a;
        v.w *= a;
        return v;
    }

    Vec4& operator/=(Vec4& v, f32 a) {
        v.x /= a;
        v.y /= a;
        v.z /= a;
        v.w /= a;
        return v;
    }

    Vec4 operator+(Vec4 const& a, Vec4 const& b) {
        return {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
    }

    Vec4 operator-(Vec4 const& a, Vec4 const& b) {
        return {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
    }

    Vec4 operator*(Vec4 const& a, Vec4 const& b) {
        return {a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
    }

    Vec4 operator/(Vec4 const& a, Vec4 const& b) {
        return {a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w};
    }

    Vec4 operator+(Vec4 const& a, f32 b) {
        return {a.x + b, a.y + b, a.z + b, a.w + b};
    }

    Vec4 operator-(Vec4 const& a, f32 b) {
        return {a.x - b, a.y - b, a.z - b, a.w - b};
    }

    Vec4 operator*(Vec4 const& a, f32 b) {
        return {a.x * b, a.y * b, a.z * b, a.w * b};
    }

    Vec4 operator*(f32 b, Vec4 const& a) {
        return {a.x * b, a.y * b, a.z * b, a.w * b};
    }

    Vec4 operator/(Vec4 const& a, f32 b) {
        return {a.x / b, a.y / b, a.z / b, a.w / b};
    }

    bool operator==(Vec4 const& a, Vec4 const& b) {
        return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
    }

    bool operator!=(Vec4 const& a, Vec4 const& b) {
        return a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w;
    }

    Vec4 max(Vec4 const& v1, Vec4 const& v2) {
        return {v1.x > v2.x ? v1.x : v2.x, v1.y > v2.y ? v1.y : v2.y, v1.z > v2.z ? v1.z : v2.z, v1.w > v2.w ? v1.w : v2.w};
    }

    Vec4 min(Vec4 const& v1, Vec4 const& v2) {
        return {v1.x < v2.x ? v1.x : v2.x, v1.y < v2.y ? v1.y : v2.y, v1.z < v2.z ? v1.z : v2.z, v1.w < v2.w ? v1.w : v2.w};
    }

    bool is_almost_zero(Vec4 const& v, f32 const tolerance /* = 0.000001f */) {
        return math::abs(v.x) <= tolerance && math::abs(v.y) <= tolerance && math::abs(v.z) <= tolerance && math::abs(v.w) <= tolerance;
    }

    f32 dot(Vec4 const& v1, Vec4 const& v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
    }

    f32 length_squared(Vec4 const& v) {
        return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
    }

    f32 length(Vec4 const& v) {
        return math::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    }

    Vec4 normalize(Vec4 vec, f32 const tolerance /*  = 0.000001f */) {
        if(!is_almost_zero(vec, tolerance)) {
            f32 const inverse_vec_length = math::inv_sqrt(length_squared(vec));
            return vec * inverse_vec_length;
        } else {
            return Vec4{};
        }
    }

    Vec4 lerp(Vec4 const& a, Vec4 const& b, f32 const t) {
        return (1.0f - t) * a + t * b;
    }

    Vec4 slerp(Vec4 const& a, Vec4 const& b, f32 const t) {
        Vec4 const norm_a = normalize(a);
        Vec4 const norm_b = normalize(b);
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

    void swap(Vec4& a, Vec4& b) {
        detail::swap(a.x, b.x);
        detail::swap(a.y, b.y);
        detail::swap(a.z, b.z);
        detail::swap(a.w, b.w);
    }
}
