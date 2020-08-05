#pragma once

#include <anton/math/math.hpp>
#include <anton/math/matrix4.hpp>
#include <anton/math/quaternion.hpp>
#include <anton/math/vector3.hpp>

namespace anton::math {
    inline Matrix4 translate(Vector3 translation) {
        return {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {translation.x, translation.y, translation.z, 1}};
    }

    inline Matrix4 rotate(Quaternion q) {
        return {{1 - 2 * q.y * q.y - 2 * q.z * q.z, 2 * q.x * q.y + 2 * q.z * q.w, 2 * q.x * q.z - 2 * q.y * q.w, 0},
                {2 * q.x * q.y - 2 * q.z * q.w, 1 - 2 * q.x * q.x - 2 * q.z * q.z, 2 * q.y * q.z + 2 * q.x * q.w, 0},
                {2 * q.x * q.z + 2 * q.y * q.w, 2 * q.y * q.z - 2 * q.x * q.w, 1 - 2 * q.x * q.x - 2 * q.y * q.y, 0},
                {0, 0, 0, 1}};
    }

    inline Matrix4 rotate_x(f32 angle) {
        f32 sin_val = math::sin(angle);
        f32 cos_val = math::cos(angle);
        return {{1, 0, 0, 0}, {0, cos_val, -sin_val, 0}, {0, sin_val, cos_val, 0}, {0, 0, 0, 1}};
    }

    inline Matrix4 rotate_y(f32 angle) {
        f32 sin_val = math::sin(angle);
        f32 cos_val = math::cos(angle);
        return {{cos_val, 0, sin_val, 0}, {0, 1, 0, 0}, {-sin_val, 0, cos_val, 0}, {0, 0, 0, 1}};
    }

    inline Matrix4 rotate_z(f32 angle) {
        f32 sin_val = math::sin(angle);
        f32 cos_val = math::cos(angle);
        return {{cos_val, -sin_val, 0, 0}, {sin_val, cos_val, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
    }

    // scale
    // Construct a varying scale transformation matrix.
    //
    inline Matrix4 scale(Vector3 scale) {
        return {{scale.x, 0, 0, 0}, {0, scale.y, 0, 0}, {0, 0, scale.z, 0}, {0, 0, 0, 1}};
    }

    // scale
    // Construct a uniform scale transformation matrix.
    //
    inline Matrix4 scale(f32 scale) {
        return {{scale, 0, 0, 0}, {0, scale, 0, 0}, {0, 0, scale, 0}, {0, 0, 0, 1}};
    }

    // orthographic_rh
    // Calculates orthographic projection matrix to [-1, 1] clip space for right-handed coordinate system.
    //
    inline Matrix4 orthographic_rh(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far) {
        return {{2.0f / (right - left), 0, 0, 0},
                {0, 2.0f / (top - bottom), 0, 0},
                {0, 0, -2.0f / (far - near), 0},
                {-(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1}};
    }

    // orthographic_lh
    // Calculates orthographic projection matrix to [-1, 1] clip space for left-handed coordinate system.
    //
    inline Matrix4 orthographic_lh(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far) {
        return {{2.0f / (right - left), 0, 0, 0},
                {0, 2.0f / (top - bottom), 0, 0},
                {0, 0, 2.0f / (far - near), 0},
                {-(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1}};
    }

    // perspective_rh
    // Calculates perspective projection matrix to [-1, 1] clip space for right-handed coordinate system.
    //
    // fov - angle in radians.
    // aspect_ratio - ratio of width to height.
    // near and far are the positions of near and far planes respectively.
    //
    inline Matrix4 perspective_rh(f32 const fov, f32 const aspect_ratio, f32 const near, f32 const far) {
        f32 inv_tan = 1 / (math::tan(fov / 2));
        return {{inv_tan / aspect_ratio, 0, 0, 0}, {0, inv_tan, 0, 0}, {0, 0, -(far + near) / (far - near), -1}, {0, 0, -2 * far * near / (far - near), 0}};
    }

    // perspective_rh_zo
    // Calculates perspective projection matrix to [0, 1] clip space for right-handed coordinate system.
    //
    // fov - angle in radians.
    // aspect_ratio - ratio of width to height.
    // near and far are the positions of near and far planes respectively.
    //
    inline Matrix4 perspective_rh_zo(f32 const fov, f32 const aspect_ratio, f32 const near, f32 const far) {
        f32 inv_tan = 1 / (math::tan(fov / 2));
        return {{inv_tan / aspect_ratio, 0, 0, 0}, {0, inv_tan, 0, 0}, {0, 0, -far / (far - near), -1}, {0, 0, -1 * far * near / (far - near), 0}};
    }

    // perspective_lh
    // Calculates perspective projection matrix to [-1, 1] clip space for left-handed coordinate system.
    //
    // fov - angle in radians.
    // aspect_ratio - ratio of width to height.
    // near and far are the positions of near and far planes respectively.
    //
    inline Matrix4 perspective_lh(f32 const fov, f32 const aspect_ratio, f32 const near, f32 const far) {
        f32 inv_tan = 1 / (math::tan(fov / 2));
        return {{inv_tan / aspect_ratio, 0, 0, 0}, {0, inv_tan, 0, 0}, {0, 0, (far + near) / (far - near), 1}, {0, 0, -2 * near * far / (far - near), 0}};
    }

    // lookat_rh
    // Calculates the view matrix for looking at a point for right-handed coordinate systems.
    //
    // eye - position of the eye.
    // center - point to look at.
    // up - orients the resulting view to have this vector as "up".
    //
    inline Matrix4 lookat_rh(Vector3 const& eye, Vector3 const& center, Vector3 const& up) {
        Vector3 const f = normalize(center - eye);
        Vector3 const s = normalize(cross(f, up));
        Vector3 const u = cross(s, f);
        Matrix4 r = {};
        r[0][0] = s.x;
        r[1][0] = s.y;
        r[2][0] = s.z;
        r[0][1] = u.x;
        r[1][1] = u.y;
        r[2][1] = u.z;
        r[0][2] = -f.x;
        r[1][2] = -f.y;
        r[2][2] = -f.z;
        r[3][0] = -dot(s, eye);
        r[3][1] = -dot(u, eye);
        r[3][2] = dot(f, eye);
        r[3][3] = 1.f;
        return r;
    }

    struct Decomposed_Matrix {
        Quaternion rotation;
        Vector3 translation;
        Vector3 scale;
    };

    // decompose
    // Decomposes a simple transformation matrix (translation, rotation, (non-uniform) scale)
    // into individual elements.
    //
    inline Decomposed_Matrix decompose(Matrix4 const matrix) {
        Vector3 translation = Vector3(matrix[3]);
        Vector3 scale = {length(Vector3(matrix[0])), length(Vector3(matrix[1])), length(Vector3(matrix[2]))};
        f32 const m00 = matrix[0][0] / scale.x;
        f32 const m01 = matrix[0][1] / scale.x;
        f32 const m02 = matrix[0][2] / scale.x;
        f32 const m10 = matrix[1][0] / scale.y;
        f32 const m11 = matrix[1][1] / scale.y;
        f32 const m12 = matrix[1][2] / scale.y;
        f32 const m20 = matrix[2][0] / scale.z;
        f32 const m21 = matrix[2][1] / scale.z;
        f32 const m22 = matrix[2][2] / scale.z;
        f32 const trace = m00 + m11 + m22;
        f32 qw, qx, qy, qz;
        if(trace > 0.0f) {
            qw = math::sqrt(1.0f + trace) * 0.5f;
            qx = 0.25f * (m12 - m21) / qw;
            qy = 0.25f * (m20 - m02) / qw;
            qz = 0.25f * (m01 - m10) / qw;
        } else if(m00 > m11 && m00 > m22) {
            qx = math::sqrt(1.0f + m00 - m11 - m22) * 0.5f;
            qy = 0.25f * (m01 + m10) / qx;
            qz = 0.25f * (m02 + m20) / qx;
            qw = 0.25f * (m12 - m21) / qx;
        } else if(m11 > m22) {
            qy = math::sqrt(1.0f + m11 - m00 - m22) * 0.5f;
            qx = 0.25f * (m01 + m10) / qy;
            qz = 0.25f * (m12 + m21) / qy;
            qw = 0.25f * (m20 - m02) / qy;
        } else {
            qz = math::sqrt(1.0f + m22 - m00 - m11) * 0.5f;
            qx = 0.25f * (m02 + m20) / qz;
            qy = 0.25f * (m12 + m21) / qz;
            qw = 0.25f * (m01 + m10) / qz;
        }
        return {{qx, qy, qz, qw}, translation, scale};
    }
} // namespace anton::math
