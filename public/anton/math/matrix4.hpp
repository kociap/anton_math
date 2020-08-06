#pragma once

#include <anton/math/math.hpp>
#include <anton/math/vector4.hpp>
#include <anton/math/detail/utility.hpp>

namespace anton::math {
    // Column major
    struct Matrix4 {
    public:
        static Matrix4 const zero;
        static Matrix4 const identity;

        Matrix4(): columns{} {}
        Matrix4(Vector4 const a, Vector4 const b, Vector4 const c, Vector4 const d): columns{a, b, c, d} {}
        explicit Matrix4(f32 const* const p): columns{Vector4{p}, Vector4{p + 4}, Vector4{p + 8}, Vector4{p + 12}} {}

        Vector4& operator[](i32 const column) {
            return columns[column];
        }

        Vector4 operator[](i32 const column) const {
            return columns[column];
        }

        f32& operator()(i32 const column, i32 const row) {
            return columns[column][row];
        }

        f32 operator()(i32 const column, i32 const row) const {
            return columns[column][row];
        }

        f32 const* data() const {
            return (f32 const*)columns;
        }

        Matrix4& operator+=(f32 const a) {
            columns[0] += a;
            columns[1] += a;
            columns[2] += a;
            columns[3] += a;
            return *this;
        }

        Matrix4& operator-=(f32 const a) {
            columns[0] -= a;
            columns[1] -= a;
            columns[2] -= a;
            columns[3] -= a;
            return *this;
        }

        Matrix4& operator*=(f32 const a) {
            columns[0] *= a;
            columns[1] *= a;
            columns[2] *= a;
            columns[3] *= a;
            return *this;
        }

        Matrix4& operator/=(f32 const a) {
            columns[0] /= a;
            columns[1] /= a;
            columns[2] /= a;
            columns[3] /= a;
            return *this;
        }

        Matrix4& operator+=(Matrix4 const m) {
            columns[0] += m.columns[0];
            columns[1] += m.columns[1];
            columns[2] += m.columns[2];
            columns[3] += m.columns[3];
            return *this;
        }

        Matrix4& operator-=(Matrix4 const m) {
            columns[0] -= m.columns[0];
            columns[1] -= m.columns[1];
            columns[2] -= m.columns[2];
            columns[3] -= m.columns[3];
            return *this;
        }

        Matrix4& operator*=(Matrix4 const rhs) {
            Matrix4 const lhs = *this;
            for (i32 i = 0; i < 4; ++i) {
                (*this)[i][0] = rhs[i][0] * lhs[0][0] + rhs[i][1] * lhs[1][0] + rhs[i][2] * lhs[2][0] + rhs[i][3] * lhs[3][0];
                (*this)[i][1] = rhs[i][0] * lhs[0][1] + rhs[i][1] * lhs[1][1] + rhs[i][2] * lhs[2][1] + rhs[i][3] * lhs[3][1];
                (*this)[i][2] = rhs[i][0] * lhs[0][2] + rhs[i][1] * lhs[1][2] + rhs[i][2] * lhs[2][2] + rhs[i][3] * lhs[3][2];
                (*this)[i][3] = rhs[i][0] * lhs[0][3] + rhs[i][1] * lhs[1][3] + rhs[i][2] * lhs[2][3] + rhs[i][3] * lhs[3][3];
            }
            return *this;
        }

    private:
        Vector4 columns[4];
    };

    inline Matrix4 const Matrix4::zero = Matrix4();
    inline Matrix4 const Matrix4::identity = Matrix4{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

    inline Matrix4 operator+(Matrix4 m, f32 const a) {
        m += a;
        return m;
    }

    inline Matrix4 operator-(Matrix4 m, f32 const a) {
        m -= a;
        return m;
    }

    inline Matrix4 operator*(Matrix4 m, f32 const a) {
        m *= a;
        return m;
    }

    inline Matrix4 operator/(Matrix4 m, f32 const a) {
        m /= a;
        return m;
    }

    inline Matrix4 operator+(Matrix4 lhs, Matrix4 const rhs) {
        lhs += rhs;
        return lhs;
    }

    inline Matrix4 operator-(Matrix4 lhs, Matrix4 const rhs) {
        lhs -= rhs;
        return lhs;
    }

    inline Matrix4 operator*(Matrix4 lhs, Matrix4 const rhs) {
        lhs *= rhs;
        return lhs;
    }

    inline Vector4 operator*(Matrix4 const lhs, Vector4 const rhs) {
        Vector4 r;
        r[0] = rhs[0] * lhs[0][0] + rhs[1] * lhs[1][0] + rhs[2] * lhs[2][0] + rhs[3] * lhs[3][0];
        r[1] = rhs[0] * lhs[0][1] + rhs[1] * lhs[1][1] + rhs[2] * lhs[2][1] + rhs[3] * lhs[3][1];
        r[2] = rhs[0] * lhs[0][2] + rhs[1] * lhs[1][2] + rhs[2] * lhs[2][2] + rhs[3] * lhs[3][2];
        r[3] = rhs[0] * lhs[0][3] + rhs[1] * lhs[1][3] + rhs[2] * lhs[2][3] + rhs[3] * lhs[3][3];
        return r;
    }

    inline Matrix4 transpose(Matrix4 mat) {
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

    inline f32 determinant(Matrix4 const m) {
        f32 det0 = _determinant3x3(m[1][1], m[1][2], m[1][3], m[2][1], m[2][2], m[2][3], m[3][1], m[3][2], m[3][3]);
        f32 det1 = _determinant3x3(m[1][0], m[1][2], m[1][3], m[2][0], m[2][2], m[2][3], m[3][0], m[3][2], m[3][3]);
        f32 det2 = _determinant3x3(m[1][0], m[1][1], m[1][3], m[2][0], m[2][1], m[2][3], m[3][0], m[3][1], m[3][3]);
        f32 det3 = _determinant3x3(m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2], m[3][0], m[3][1], m[3][2]);
        return m[0][0] * det0 - m[0][1] * det1 + m[0][2] * det2 - m[0][3] * det3;
    }

    inline Matrix4 adjugate(Matrix4 const m) {
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
        return Matrix4(
            {m00, -m10, m20, -m30}, 
            {-m01, m11, -m21, m31}, 
            {m02, -m12, m22, -m32}, 
            {-m03, m13, -m23, m33});
    }

    inline Matrix4 inverse(Matrix4 const m) {
        return adjugate(m) / determinant(m);
    }

    inline void swap(Matrix4& m1, Matrix4& m2) {
        detail::swap(m1[0], m2[0]);
        detail::swap(m1[1], m2[1]);
        detail::swap(m1[2], m2[2]);
        detail::swap(m1[3], m2[3]);
    }
} // namespace anton::math
