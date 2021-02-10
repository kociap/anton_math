#include <anton/math/vec2.hpp>
#include <anton/math/vec3.hpp>
#include <anton/math/vec4.hpp>
#include <detail/utility.hpp>

namespace anton::math {
    Vec2::Vec2(): x(0.0f), y(0.0f) {}
    Vec2::Vec2(f32 v): x(v), y(v) {}
    Vec2::Vec2(f32 x, f32 y): x(x), y(y) {}
    Vec2::Vec2(Vec3 const& vec): x(vec.x), y(vec.y) {}
    Vec2::Vec2(Vec4 const& vec): x(vec.x), y(vec.y) {}
    Vec2::Vec2(f32 const* const p): x(p[0]), y(p[1]) {}

    f32& Vec2::operator[](i32 index) {
        return (&x)[index];
    }

    f32 const& Vec2::operator[](i32 index) const {
        return (&x)[index];
    }

    f32* Vec2::data() {
        return &x;
    }

    f32 const* Vec2::data() const {
        return &x;
    }

    Vec2 operator-(Vec2 const& v) {
        return {-v.x, -v.y};
    }

    Vec2& operator+=(Vec2& v, Vec2 const& a) {
        v.x += a.x;
        v.y += a.y;
        return v;
    }

    Vec2& operator-=(Vec2& v, Vec2 const& a) {
        v.x -= a.x;
        v.y -= a.y;
        return v;
    }

    Vec2& operator+=(Vec2& v, f32 a) {
        v.x += a;
        v.y += a;
        return v;
    }

    Vec2& operator*=(Vec2& v, Vec2 const& a) {
        v.x *= a.x;
        v.y *= a.y;
        return v;
    }

    Vec2& operator/=(Vec2& v, Vec2 const& a) {
        v.x /= a.x;
        v.y /= a.y;
        return v;
    }

    Vec2& operator-=(Vec2& v, f32 a) {
        v.x -= a;
        v.y -= a;
        return v;
    }

    Vec2& operator*=(Vec2& v, f32 a) {
        v.x *= a;
        v.y *= a;
        return v;
    }

    Vec2& operator/=(Vec2& v, f32 a) {
        v.x /= a;
        v.y /= a;
        return v;
    }

    Vec2 operator+(Vec2 const& a, Vec2 const& b) {
        return {a.x + b.x, a.y + b.y};
    }

    Vec2 operator-(Vec2 const& a, Vec2 const& b) {
        return {a.x - b.x, a.y - b.y};
    }

    Vec2 operator*(Vec2 const& a, Vec2 const& b) {
        return {a.x * b.x, a.y * b.y};
    }

    Vec2 operator/(Vec2 const& a, Vec2 const& b) {
        return {a.x / b.x, a.y / b.y};
    }

    Vec2 operator+(Vec2 const& a, f32 b) {
        return {a.x + b, a.y + b};
    }

    Vec2 operator-(Vec2 const& a, f32 b) {
        return {a.x - b, a.y - b};
    }

    Vec2 operator*(Vec2 const& a, f32 b) {
        return {a.x * b, a.y * b};
    }

    Vec2 operator*(f32 b, Vec2 const& a) {
        return {a.x * b, a.y * b};
    }

    Vec2 operator/(Vec2 const& a, f32 b) {
        return {a.x / b, a.y / b};
    }

    bool operator==(Vec2 const& a, Vec2 const& b) {
        return a.x == b.x && a.y == b.y;
    }

    bool operator!=(Vec2 const& a, Vec2 const& b) {
        return a.x != b.x || a.y != b.y;
    }

    Vec2 max(Vec2 const& v1, Vec2 const& v2) {
        return {v1.x > v2.x ? v1.x : v2.x, v1.y > v2.y ? v1.y : v2.y};
    }

    Vec2 min(Vec2 const& v1, Vec2 const& v2) {
        return {v1.x < v2.x ? v1.x : v2.x, v1.y < v2.y ? v1.y : v2.y};
    }

    bool is_almost_zero(Vec2 const& v, f32 const tolerance /* = 0.000001f */) {
        return math::abs(v.x) <= tolerance && math::abs(v.y) <= tolerance;
    }

    f32 dot(Vec2 const& vec1, Vec2 const& vec2) {
        return vec1.x * vec2.x + vec1.y * vec2.y;
    }

    f32 length_squared(Vec2 const& v) {
        return v.x * v.x + v.y * v.y;
    }

    f32 length(Vec2 const& v) {
        return math::sqrt(v.x * v.x + v.y * v.y);
    }

    Vec2 normalize(Vec2 vec, f32 const tolerance /* = 0.000001f */) {
        if(!is_almost_zero(vec, tolerance)) {
            f32 const inverse_vec_length = math::inv_sqrt(length_squared(vec));
            return vec * inverse_vec_length;
        } else {
            return Vec2{};
        }
    }

    Vec2 lerp(Vec2 const& a, Vec2 const& b, f32 const t) {
        return (1.0f - t) * a + t * b;
    }

    Vec2 slerp(Vec2 const& a, Vec2 const& b, f32 const t) {
        Vec2 const norm_a = normalize(a);
        Vec2 const norm_b = normalize(b);
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

    void swap(Vec2& a, Vec2& b) {
        detail::swap(a.x, b.x);
        detail::swap(a.y, b.y);
    }
}
