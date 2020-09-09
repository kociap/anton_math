#pragma once

#include <anton/math/math.hpp>
#include <anton/math/vec4.hpp>
#include <anton/math/detail/utility.hpp>

namespace anton::math {
    // Column major
    struct Mat4 {
    public:
        static Mat4 const zero;
        static Mat4 const identity;

        Mat4(): columns{} {}
        Mat4(Vec4 const a, Vec4 const b, Vec4 const c, Vec4 const d): columns{a, b, c, d} {}
        explicit Mat4(f32 const* const p): columns{Vec4{p}, Vec4{p + 4}, Vec4{p + 8}, Vec4{p + 12}} {}

        Vec4& operator[](i32 const column) {
            return columns[column];
        }

        Vec4 operator[](i32 const column) const {
            return columns[column];
        }

        f32& operator()(i32 const column, i32 const row) {
            return columns[column][row];
        }

        f32 operator()(i32 const column, i32 const row) const {
            return columns[column][row];
        }

        f32* data()  {
            return (f32*)columns;
        }

        f32 const* data() const {
            return (f32 const*)columns;
        }

        Mat4& operator+=(f32 const a) {
            columns[0] += a;
            columns[1] += a;
            columns[2] += a;
            columns[3] += a;
            return *this;
        }

        Mat4& operator-=(f32 const a) {
            columns[0] -= a;
            columns[1] -= a;
            columns[2] -= a;
            columns[3] -= a;
            return *this;
        }

        Mat4& operator*=(f32 const a) {
            columns[0] *= a;
            columns[1] *= a;
            columns[2] *= a;
            columns[3] *= a;
            return *this;
        }

        Mat4& operator/=(f32 const a) {
            columns[0] /= a;
            columns[1] /= a;
            columns[2] /= a;
            columns[3] /= a;
            return *this;
        }

        Mat4& operator+=(Mat4 const m) {
            columns[0] += m.columns[0];
            columns[1] += m.columns[1];
            columns[2] += m.columns[2];
            columns[3] += m.columns[3];
            return *this;
        }

        Mat4& operator-=(Mat4 const m) {
            columns[0] -= m.columns[0];
            columns[1] -= m.columns[1];
            columns[2] -= m.columns[2];
            columns[3] -= m.columns[3];
            return *this;
        }

        Mat4& operator*=(Mat4 const rhs) {
            Mat4 const lhs = *this;
            for (i32 i = 0; i < 4; ++i) {
                (*this)[i][0] = rhs[i][0] * lhs[0][0] + rhs[i][1] * lhs[1][0] + rhs[i][2] * lhs[2][0] + rhs[i][3] * lhs[3][0];
                (*this)[i][1] = rhs[i][0] * lhs[0][1] + rhs[i][1] * lhs[1][1] + rhs[i][2] * lhs[2][1] + rhs[i][3] * lhs[3][1];
                (*this)[i][2] = rhs[i][0] * lhs[0][2] + rhs[i][1] * lhs[1][2] + rhs[i][2] * lhs[2][2] + rhs[i][3] * lhs[3][2];
                (*this)[i][3] = rhs[i][0] * lhs[0][3] + rhs[i][1] * lhs[1][3] + rhs[i][2] * lhs[2][3] + rhs[i][3] * lhs[3][3];
            }
            return *this;
        }

    private:
        Vec4 columns[4];
    };

    inline Mat4 const Mat4::zero = Mat4();
    inline Mat4 const Mat4::identity = Mat4{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

    inline Mat4 operator+(Mat4 m, f32 const a) {
        m += a;
        return m;
    }

    inline Mat4 operator-(Mat4 m, f32 const a) {
        m -= a;
        return m;
    }

    inline Mat4 operator*(Mat4 m, f32 const a) {
        m *= a;
        return m;
    }

    inline Mat4 operator/(Mat4 m, f32 const a) {
        m /= a;
        return m;
    }

    inline Mat4 operator+(Mat4 lhs, Mat4 const rhs) {
        lhs += rhs;
        return lhs;
    }

    inline Mat4 operator-(Mat4 lhs, Mat4 const rhs) {
        lhs -= rhs;
        return lhs;
    }

    inline Mat4 operator*(Mat4 lhs, Mat4 const rhs) {
        lhs *= rhs;
        return lhs;
    }

    inline Vec4 operator*(Mat4 const lhs, Vec4 const rhs) {
        Vec4 r;
        r[0] = rhs[0] * lhs[0][0] + rhs[1] * lhs[1][0] + rhs[2] * lhs[2][0] + rhs[3] * lhs[3][0];
        r[1] = rhs[0] * lhs[0][1] + rhs[1] * lhs[1][1] + rhs[2] * lhs[2][1] + rhs[3] * lhs[3][1];
        r[2] = rhs[0] * lhs[0][2] + rhs[1] * lhs[1][2] + rhs[2] * lhs[2][2] + rhs[3] * lhs[3][2];
        r[3] = rhs[0] * lhs[0][3] + rhs[1] * lhs[1][3] + rhs[2] * lhs[2][3] + rhs[3] * lhs[3][3];
        return r;
    }

    inline Mat4 transpose(Mat4 mat) {
        detail::swap(mat[0][1], mat[1][0]);
        detail::swap(mat[0][2], mat[2][0]);
        detail::swap(mat[0][3], mat[3][0]);
        detail::swap(mat[1][2], mat[2][1]);
        detail::swap(mat[1][3], mat[3][1]);
        detail::swap(mat[2][3], mat[3][2]);
        return mat;
    }

    inline static f32 _determinant3x3(f32 m00, f32 m01, f32 m02, f32 m10, f32 m11, f32 m12, f32 m20, f32 m21, f32 m22) {
        return m00 * m11 * m22 + m01 * m12 * m20 + m02 * m10 * m21 - m02 * m11 * m20 - m01 * m10 * m22 - m00 * m12 * m21;
    }

    inline f32 determinant(Mat4 const m) {
        f32 det0 = _determinant3x3(m[1][1], m[1][2], m[1][3], m[2][1], m[2][2], m[2][3], m[3][1], m[3][2], m[3][3]);
        f32 det1 = _determinant3x3(m[1][0], m[1][2], m[1][3], m[2][0], m[2][2], m[2][3], m[3][0], m[3][2], m[3][3]);
        f32 det2 = _determinant3x3(m[1][0], m[1][1], m[1][3], m[2][0], m[2][1], m[2][3], m[3][0], m[3][1], m[3][3]);
        f32 det3 = _determinant3x3(m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2], m[3][0], m[3][1], m[3][2]);
        return m[0][0] * det0 - m[0][1] * det1 + m[0][2] * det2 - m[0][3] * det3;
    }

    inline Mat4 adjugate(Mat4 const m) {
        f32 m00 = _determinant3x3(m[1][1], m[1][2], m[1][3], m[2][1], m[2][2], m[2][3], m[3][1], m[3][2], m[3][3]);
        f32 m01 = _determinant3x3(m[1][0], m[1][2], m[1][3], m[2][0], m[2][2], m[2][3], m[3][0], m[3][2], m[3][3]);
        f32 m02 = _determinant3x3(m[1][0], m[1][1], m[1][3], m[2][0], m[2][1], m[2][3], m[3][0], m[3][1], m[3][3]);
        f32 m03 = _determinant3x3(m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2], m[3][0], m[3][1], m[3][2]);

        f32 m10 = _determinant3x3(m[0][1], m[0][2], m[0][3], m[2][1], m[2][2], m[2][3], m[3][1], m[3][2], m[3][3]);
        f32 m11 = _determinant3x3(m[0][0], m[0][2], m[0][3], m[2][0], m[2][2], m[2][3], m[3][0], m[3][2], m[3][3]);
        f32 m12 = _determinant3x3(m[0][0], m[0][1], m[0][3], m[2][0], m[2][1], m[2][3], m[3][0], m[3][1], m[3][3]);
        f32 m13 = _determinant3x3(m[0][0], m[0][1], m[0][2], m[2][0], m[2][1], m[2][2], m[3][0], m[3][1], m[3][2]);

        f32 m20 = _determinant3x3(m[0][1], m[0][2], m[0][3], m[1][1], m[1][2], m[1][3], m[3][1], m[3][2], m[3][3]);
        f32 m21 = _determinant3x3(m[0][0], m[0][2], m[0][3], m[1][0], m[1][2], m[1][3], m[3][0], m[3][2], m[3][3]);
        f32 m22 = _determinant3x3(m[0][0], m[0][1], m[0][3], m[1][0], m[1][1], m[1][3], m[3][0], m[3][1], m[3][3]);
        f32 m23 = _determinant3x3(m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[3][0], m[3][1], m[3][2]);

        f32 m30 = _determinant3x3(m[0][1], m[0][2], m[0][3], m[1][1], m[1][2], m[1][3], m[2][1], m[2][2], m[2][3]);
        f32 m31 = _determinant3x3(m[0][0], m[0][2], m[0][3], m[1][0], m[1][2], m[1][3], m[2][0], m[2][2], m[2][3]);
        f32 m32 = _determinant3x3(m[0][0], m[0][1], m[0][3], m[1][0], m[1][1], m[1][3], m[2][0], m[2][1], m[2][3]);
        f32 m33 = _determinant3x3(m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2]);
        return Mat4(
            {m00, -m10, m20, -m30}, 
            {-m01, m11, -m21, m31}, 
            {m02, -m12, m22, -m32}, 
            {-m03, m13, -m23, m33});
    }

    inline Mat4 inverse(Mat4 const m) {
        return adjugate(m) / determinant(m);
    }

    inline void swap(Mat4& m1, Mat4& m2) {
        detail::swap(m1[0], m2[0]);
        detail::swap(m1[1], m2[1]);
        detail::swap(m1[2], m2[2]);
        detail::swap(m1[3], m2[3]);
    }
} // namespace anton::math
