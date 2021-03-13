#pragma once

#include <anton/types.hpp>
#include <anton/math/mat4.hpp>
#include <anton/math/quat.hpp>
#include <anton/math/vec3.hpp>

namespace anton::math {
    // translate
    // Constructs a translation matrix that performs translation by the vector translation.
    //
    // Parameters:
    // translation - the translation vector.
    //
    // Returns:
    // Transformation matrix that translates by the translation vector.
    //
    [[nodiscard]] Mat4 translate(Vec3 translation);

    // rotate
    // Constructs a rotation matrix that performs rotation by quaternion q.
    //
    // Parameters:
    // q - unit quaternion.
    //
    // Returns:
    // Transformation matrix that rotates by q.
    //
    [[nodiscard]] Mat4 rotate(Quat q);

    // rotate_x
    // Constructs a rotation matrix that performs rotation about x axis by angle.
    //
    // Parameters:
    // angle - angle of rotation in radians.
    //
    // Returns:
    // Transformation matrix that rotates about x by angle.
    //
    [[nodiscard]] Mat4 rotate_x(f32 angle);

    // rotate_y
    // Constructs a rotation matrix that performs rotation about y axis by angle.
    //
    // Parameters:
    // angle - angle of rotation in radians.
    //
    // Returns:
    // Transformation matrix that rotates about y by angle.
    //
    [[nodiscard]] Mat4 rotate_y(f32 angle);

    // rotate_z
    // Constructs a rotation matrix that performs rotation about z axis by angle.
    //
    // Parameters:
    // angle - angle of rotation in radians.
    //
    // Returns:
    // Transformation matrix that rotates about z by angle.
    //
    [[nodiscard]] Mat4 rotate_z(f32 angle);

    // scale
    // Constructs a non-uniform scale transform.
    //
    // Parameters:
    // scale - scale factors. Each component scales along the corresponding axis.
    //
    // Returns:
    // Non-uniform scale transformation matrix.
    //
    [[nodiscard]] Mat4 scale(Vec3 scale);

    // scale
    // Construct a uniform scale tansform.
    //
    // Parameters:
    // scale - uniform scale factor.
    //
    // Returns:
    // Uniform scale transformation matrix.
    //
    [[nodiscard]] Mat4 scale(f32 scale);

    // orthographic_rh
    // Calculates orthographic projection mat to [-1, 1] clip space for right-handed coordinate system.
    //
    [[nodiscard]] Mat4 orthographic_rh(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);

    // orthographic_lh
    // Calculates orthographic projection mat to [-1, 1] clip space for left-handed coordinate system.
    //
    [[nodiscard]] Mat4 orthographic_lh(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);

    // perspective_rh
    // Calculates perspective projection mat to [-1, 1] clip space for right-handed coordinate system.
    //
    // Parameters:
    // fov          - angle in radians.
    // aspect_ratio - ratio of width to height.
    // near         - position of near plane.
    // far          - position of the far plane.
    //
    [[nodiscard]] Mat4 perspective_rh(f32 fov, f32 aspect_ratio, f32 near, f32 far);

    // perspective_rh_zo
    // Calculates perspective projection mat to [0, 1] clip space for right-handed coordinate system.
    //
    // Parameters:
    // fov          - angle in radians.
    // aspect_ratio - ratio of width to height.
    // near         - position of near plane.
    // far          - position of the far plane.
    //
    [[nodiscard]] Mat4 perspective_rh_zo(f32 fov, f32 aspect_ratio, f32 near, f32 far);

    // perspective_lh
    // Calculates perspective projection mat to [-1, 1] clip space for left-handed coordinate system.
    //
    // Parameters:
    // fov          - angle in radians.
    // aspect_ratio - ratio of width to height.
    // near         - position of near plane.
    // far          - position of the far plane.
    //
    [[nodiscard]] Mat4 perspective_lh(f32 fov, f32 aspect_ratio, f32 near, f32 far);

    // lookat_rh
    // Calculates the view mat for looking at a point for right-handed coordinate systems.
    //
    // eye - position of the eye.
    // center - point to look at.
    // up - orients the resulting view to have this vec as "up".
    //
    [[nodiscard]] Mat4 lookat_rh(Vec3 const& eye, Vec3 const& center, Vec3 const& up);

    struct Decomposed_Mat {
        Quat rotation;
        Vec3 translation;
        Vec3 scale;
    };

    // decompose
    // Decomposes a simple transformation mat (translation, rotation, (non-uniform) scale)
    // into individual elements.
    //
    [[nodiscard]] Decomposed_Mat decompose(Mat4 const& mat);
} // namespace anton::math
