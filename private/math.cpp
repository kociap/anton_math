#include <anton/math/vec2.hpp>
#include <anton/math/vec3.hpp>
#include <anton/math/vec4.hpp>

#include <anton/math/mat3.hpp>
#include <anton/math/mat4.hpp>

namespace anton::math {
    Vec2::Vec2(Vec3 const& vec): x(vec.x), y(vec.y) {}
    Vec2::Vec2(Vec4 const& vec): x(vec.x), y(vec.y) {}

    Vec3::Vec3(Vec2 const& vec, f32 z /* = 0.0f */): x(vec.x), y(vec.y), z(z) {}
    Vec3::Vec3(Vec4 const& vec): x(vec.x), y(vec.y), z(vec.z) {}

    Vec4::Vec4(Vec2 const& vec, f32 z /* = 0.0f */, f32 w /* = 0.0f */): x(vec.x), y(vec.y), z(z), w(w) {}
    Vec4::Vec4(Vec3 const& vec, f32 w /* = 0.0f */): x(vec.x), y(vec.y), z(vec.z), w(w) {}

    Mat3::Mat3(Mat4 const& mat): columns{Vec3(mat[0]), Vec3(mat[1]), Vec3(mat[2])} {}
} // namespace anton::math
