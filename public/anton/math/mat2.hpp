#pragma once

#include <anton/math/math.hpp>
#include <anton/math/vec2.hpp>
#include <anton/math/detail/utility.hpp>

namespace anton::math {
    // Column major
    struct Mat2 {
    public:
        static Mat2 const zero;
        static Mat2 const identity;

        Mat2(): columns{} {}
        Mat2(Vec2 const a, Vec2 const b): columns{a, b} {}
        explicit Mat2(f32 const* const p): columns{Vec2{p}, Vec2{p + 2}} {}

        Vec2& operator[](i32 const column) {
            return columns[column];
        }

        Vec2 operator[](i32 const column) const {
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

        Mat2& operator+=(f32 const a) {
            columns[0] += a;
            columns[1] += a;
            return *this;
        }

        Mat2& operator-=(f32 const a) {
            columns[0] -= a;
            columns[1] -= a;
            return *this;
        }

        Mat2& operator*=(f32 const a) {
            columns[0] *= a;
            columns[1] *= a;
            return *this;
        }

        Mat2& operator/=(f32 const a) {
            columns[0] /= a;
            columns[1] /= a;
            return *this;
        }

        Mat2& operator+=(Mat2 const m) {
            columns[0] += m.columns[0];
            columns[1] += m.columns[1];
            return *this;
        }

        Mat2& operator-=(Mat2 const m) {
            columns[0] -= m.columns[0];
            columns[1] -= m.columns[1];
            return *this;
        }

        Mat2& operator*=(Mat2 const rhs) {
            Mat2 const lhs = *this;
            for (i32 i = 0; i < 2; ++i) {
                (*this)[i][0] = rhs[i][0] * lhs[0][0] + rhs[i][1] * lhs[1][0];
                (*this)[i][1] = rhs[i][0] * lhs[0][1] + rhs[i][1] * lhs[1][1];
            }
            return *this;
        }

    private:
        Vec2 columns[2];
    };

    inline Mat2 const Mat2::zero = Mat2();
    inline Mat2 const Mat2::identity = Mat2({1, 0}, {0, 1});

    inline Mat2 operator+(Mat2 m, f32 const a) {
        m += a;
        return m;
    }

    inline Mat2 operator-(Mat2 m, f32 const a) {
        m -= a;
        return m;
    }

    inline Mat2 operator*(Mat2 m, f32 const a) {
        m *= a;
        return m;
    }

    inline Mat2 operator/(Mat2 m, f32 const a) {
        m /= a;
        return m;
    }

    inline Mat2 operator+(Mat2 lhs, Mat2 const rhs) {
        lhs += rhs;
        return lhs;
    }

    inline Mat2 operator-(Mat2 lhs, Mat2 const rhs) {
        lhs -= rhs;
        return lhs;
    }

    inline Mat2 operator*(Mat2 lhs, Mat2 const rhs) {
        lhs *= rhs;
        return lhs;
    }

    inline Vec2 operator*(Mat2 const lhs, Vec2 const rhs) {
        Vec2 r;
        r[0] = rhs[0] * lhs[0][0] + rhs[1] * lhs[1][0];
        r[1] = rhs[0] * lhs[0][1] + rhs[1] * lhs[1][1];
        return r;
    }

    inline Mat2 transpose(Mat2 m) {
        detail::swap(m[1][0], m[0][1]);
        return m;
    }

    inline f32 determinant(Mat2 const m) {
        return m[0][0] * m[1][1] - m[1][0] * m[0][1];
    }

    inline Mat2 adjugate(Mat2 const m) {
        return {{m[1][1], -m[0][1]}, {-m[1][0], m[0][0]}};
    }

    inline Mat2 inverse(Mat2 const m) {
        return adjugate(m) / determinant(m);
    }

    inline void swap(Mat2& m1, Mat2& m2) {
        detail::swap(m1[0], m2[0]);
        detail::swap(m1[1], m2[1]);
    }
} // namespace anton::math
