#include <anton/math/vector2.hpp>
#include <anton/math/vector3.hpp>
#include <anton/math/vector4.hpp>

#include <anton/math/matrix3.hpp>
#include <anton/math/matrix4.hpp>

namespace anton::math {
    Vector2::Vector2(Vector3 const& vec): x(vec.x), y(vec.y) {}
    Vector2::Vector2(Vector4 const& vec): x(vec.x), y(vec.y) {}

    Vector3::Vector3(Vector2 const& vec, f32 z /* = 0.0f */): x(vec.x), y(vec.y), z(z) {}
    Vector3::Vector3(Vector4 const& vec): x(vec.x), y(vec.y), z(vec.z) {}

    Vector4::Vector4(Vector2 const& vec, f32 z /* = 0.0f */, f32 w /* = 0.0f */): x(vec.x), y(vec.y), z(z), w(w) {}
    Vector4::Vector4(Vector3 const& vec, f32 w /* = 0.0f */): x(vec.x), y(vec.y), z(vec.z), w(w) {}

    Matrix3::Matrix3(Matrix4 const& matrix): columns{Vector3(matrix[0]), Vector3(matrix[1]), Vector3(matrix[2])} {}
} // namespace anton::math
