#ifndef ANTON_MATH_MATRIX3_HPP_INCLUDE
#define ANTON_MATH_MATRIX3_HPP_INCLUDE

#include <anton/math/math.hpp>
#include <anton/math/vector3.hpp>
#include <anton/math/detail/utility.hpp>

namespace anton::math {
    // Column major
    class Matrix3 {
    public:
        static Matrix3 const zero;
        static Matrix3 const identity;

        Matrix3(): columns{} {}
        Matrix3(Vector3 const a, Vector3 const b, Vector3 const c): columns{a, b, c} {}
        explicit Matrix3(f32 const* const p): columns{Vector3{p}, Vector3{p + 3}, Vector3{p + 6}} {}

        Vector3& operator[](i32 column) {
            return columns[column];
        }

        Vector3 operator[](i32 column) const {
            return columns[column];
        }

        f32& operator()(i32 const column, i32 const row) {
            return columns[column][row];
        }

        f32 operator()(i32 const column, i32 const row) const {
            return columns[column][row];
        }

        f32 const* get_raw() const {
            return (f32 const*)columns;
        }

        Matrix3& operator+=(f32 const a) {
            columns[0] += a;
            columns[1] += a;
            columns[2] += a;
            return *this;
        }

        Matrix3& operator-=(f32 const a) {
            columns[0] -= a;
            columns[1] -= a;
            columns[2] -= a;
            return *this;
        }

        Matrix3& operator*=(f32 const a) {
            columns[0] *= a;
            columns[1] *= a;
            columns[2] *= a;
            return *this;
        }

        Matrix3& operator/=(f32 const a) {
            columns[0] /= a;
            columns[1] /= a;
            columns[2] /= a;
            return *this;
        }

        Matrix3& operator+=(Matrix3 const m) {
            columns[0] += m.columns[0];
            columns[1] += m.columns[1];
            columns[2] += m.columns[2];
            return *this;
        }

        Matrix3& operator-=(Matrix3 const m) {
            columns[0] -= m.columns[0];
            columns[1] -= m.columns[1];
            columns[2] -= m.columns[2];
            return *this;
        }

        Matrix3& operator*=(Matrix3 const rhs) {
            Matrix3 const lhs = *this;
            for (i32 i = 0; i < 3; ++i) {
                (*this)[i][0] = rhs[i][0] * lhs[0][0] + rhs[i][1] * lhs[1][0] + rhs[i][2] * lhs[2][0];
                (*this)[i][1] = rhs[i][0] * lhs[0][1] + rhs[i][1] * lhs[1][1] + rhs[i][2] * lhs[2][1];
                (*this)[i][2] = rhs[i][0] * lhs[0][2] + rhs[i][1] * lhs[1][2] + rhs[i][2] * lhs[2][2];
            }
            return *this;
        }

    private:
        Vector3 columns[3];
    };

    inline Matrix3 const Matrix3::zero = Matrix3();
    inline Matrix3 const Matrix3::identity = Matrix3({1, 0, 0}, {0, 1, 0}, {0, 0, 1});

    inline Matrix3 operator+(Matrix3 m, f32 a) {
        m += a;
        return m;
    }

    inline Matrix3 operator-(Matrix3 m, f32 a) {
        m -= a;
        return m;
    }

    inline Matrix3 operator*(Matrix3 m, f32 a) {
        m *= a;
        return m;
    }

    inline Matrix3 operator/(Matrix3 m, f32 a) {
        m /= a;
        return m;
    }

    inline Matrix3 operator+(Matrix3 lhs, Matrix3 const rhs) {
        lhs += rhs;
        return lhs;
    }

    inline Matrix3 operator-(Matrix3 lhs, Matrix3 const rhs) {
        lhs -= rhs;
        return lhs;
    }

    inline Matrix3 operator*(Matrix3 lhs, Matrix3 const rhs) {
        lhs *= rhs;
        return lhs;
    }

    inline Vector3 operator*(Matrix3 const lhs, Vector3 const rhs) {
        Vector3 r;
        r[0] = rhs[0] * lhs[0][0] + rhs[1] * lhs[1][0] + rhs[2] * lhs[2][0];
        r[1] = rhs[0] * lhs[0][1] + rhs[1] * lhs[1][1] + rhs[2] * lhs[2][1];
        r[2] = rhs[0] * lhs[0][2] + rhs[1] * lhs[1][2] + rhs[2] * lhs[2][2];
        return r;
    }

    inline Matrix3 transpose(Matrix3 m) {
        detail::swap(m[0][1], m[1][0]);
        detail::swap(m[0][2], m[2][0]);
        detail::swap(m[1][2], m[2][1]);
        return m;
    }

    inline static f32 _determinant2x2(f32 m00, f32 m01, f32 m10, f32 m11) {
        return m00 * m11 - m01 * m10;
    }

    inline f32 determinant(Matrix3 const m) {
        // clang-format off
        return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) - 
               m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
               m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
        // clang-format on
    }

    inline Matrix3 adjugate(Matrix3 const m) {
        f32 m00 = _determinant2x2(m[1][1], m[1][2], m[2][1], m[2][2]);
        f32 m01 = _determinant2x2(m[1][0], m[1][2], m[2][0], m[2][2]);
        f32 m02 = _determinant2x2(m[1][0], m[1][1], m[2][0], m[2][1]);

        f32 m10 = _determinant2x2(m[0][1], m[0][2], m[2][1], m[2][2]);
        f32 m11 = _determinant2x2(m[0][0], m[0][2], m[2][0], m[2][2]);
        f32 m12 = _determinant2x2(m[0][0], m[0][1], m[2][0], m[2][1]);

        f32 m20 = _determinant2x2(m[0][1], m[0][2], m[1][1], m[1][2]);
        f32 m21 = _determinant2x2(m[0][0], m[0][2], m[1][0], m[1][2]);
        f32 m22 = _determinant2x2(m[0][0], m[0][1], m[1][0], m[1][1]);
        // clang-format off
        return Matrix3(
            {m00, -m10, m20}, 
            {-m01, m11, -m21}, 
            {m02, -m12, m22});
        // clang-format on
    }

    inline Matrix3 inverse(Matrix3 const m) {
        return adjugate(m) / determinant(m);
    }

    inline void swap(Matrix3& m1, Matrix3& m2) {
        detail::swap(m1[0], m2[0]);
        detail::swap(m1[1], m2[1]);
        detail::swap(m1[2], m2[2]);
    }
} // namespace anton::math

#endif // !ANTON_MATH_MATRIX3_HPP_INCLUDE
