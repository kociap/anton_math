#ifndef ANTON_MATH_MATRIX2_HPP_INCLUDE
#define ANTON_MATH_MATRIX2_HPP_INCLUDE

#include <anton/math/math.hpp>
#include <anton/math/vector2.hpp>
#include <anton/math/detail/utility.hpp>

namespace anton::math {
    // Column major
    class Matrix2 {
    public:
        static Matrix2 const zero;
        static Matrix2 const identity;

        Matrix2(): columns{} {}
        Matrix2(Vector2 const a, Vector2 const b): columns{a, b} {}
        explicit Matrix2(f32 const* const p): columns{Vector2{p}, Vector2{p + 2}} {}

        Vector2& operator[](i32 const column) {
            return columns[column];
        }

        Vector2 operator[](i32 const column) const {
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

        Matrix2& operator+=(f32 const a) {
            columns[0] += a;
            columns[1] += a;
            return *this;
        }

        Matrix2& operator-=(f32 const a) {
            columns[0] -= a;
            columns[1] -= a;
            return *this;
        }

        Matrix2& operator*=(f32 const a) {
            columns[0] *= a;
            columns[1] *= a;
            return *this;
        }

        Matrix2& operator/=(f32 const a) {
            columns[0] /= a;
            columns[1] /= a;
            return *this;
        }

        Matrix2& operator+=(Matrix2 const m) {
            columns[0] += m.columns[0];
            columns[1] += m.columns[1];
            return *this;
        }

        Matrix2& operator-=(Matrix2 const m) {
            columns[0] -= m.columns[0];
            columns[1] -= m.columns[1];
            return *this;
        }

        Matrix2& operator*=(Matrix2 const rhs) {
            Matrix2 const lhs = *this;
            for (i32 i = 0; i < 2; ++i) {
                (*this)[i][0] = rhs[i][0] * lhs[0][0] + rhs[i][1] * lhs[1][0];
                (*this)[i][1] = rhs[i][0] * lhs[0][1] + rhs[i][1] * lhs[1][1];
            }
            return *this;
        }

    private:
        Vector2 columns[2];
    };

    inline Matrix2 const Matrix2::zero = Matrix2();
    inline Matrix2 const Matrix2::identity = Matrix2({1, 0}, {0, 1});

    inline Matrix2 operator+(Matrix2 m, f32 const a) {
        m += a;
        return m;
    }

    inline Matrix2 operator-(Matrix2 m, f32 const a) {
        m -= a;
        return m;
    }

    inline Matrix2 operator*(Matrix2 m, f32 const a) {
        m *= a;
        return m;
    }

    inline Matrix2 operator/(Matrix2 m, f32 const a) {
        m /= a;
        return m;
    }

    inline Matrix2 operator+(Matrix2 lhs, Matrix2 const rhs) {
        lhs += rhs;
        return lhs;
    }

    inline Matrix2 operator-(Matrix2 lhs, Matrix2 const rhs) {
        lhs -= rhs;
        return lhs;
    }

    inline Matrix2 operator*(Matrix2 lhs, Matrix2 const rhs) {
        lhs *= rhs;
        return lhs;
    }

    inline Vector2 operator*(Matrix2 const lhs, Vector2 const rhs) {
        Vector2 r;
        r[0] = rhs[0] * lhs[0][0] + rhs[1] * lhs[1][0];
        r[1] = rhs[0] * lhs[0][1] + rhs[1] * lhs[1][1];
        return r;
    }

    inline Matrix2 transpose(Matrix2 m) {
        detail::swap(m[1][0], m[0][1]);
        return m;
    }

    inline f32 determinant(Matrix2 const m) {
        return m[0][0] * m[1][1] - m[1][0] * m[0][1];
    }

    inline Matrix2 adjugate(Matrix2 const m) {
        return {{m[1][1], -m[0][1]}, {-m[1][0], m[0][0]}};
    }

    inline Matrix2 inverse(Matrix2 const m) {
        return adjugate(m) / determinant(m);
    }

    inline void swap(Matrix2& m1, Matrix2& m2) {
        detail::swap(m1[0], m2[0]);
        detail::swap(m1[1], m2[1]);
    }
} // namespace anton::math

#endif // !ANTON_MATH_MATRIX2_HPP_INCLUDE
