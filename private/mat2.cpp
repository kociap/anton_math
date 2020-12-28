#include <anton/math/mat2.hpp>
#include <detail/utility.hpp>

namespace anton::math {
    Mat2 const Mat2::zero = Mat2();
    Mat2 const Mat2::identity = Mat2({1, 0}, {0, 1});

    Mat2::Mat2(): columns{} {}
    Mat2::Mat2(Vec2 const& a, Vec2 const& b): columns{a, b} {}
    Mat2::Mat2(f32 const* const p): columns{Vec2{p}, Vec2{p + 2}} {}

    Vec2& Mat2::operator[](i32 const column) {
        return columns[column];
    }

    Vec2 const& Mat2::operator[](i32 const column) const {
        return columns[column];
    }

    f32& Mat2::operator()(i32 const column, i32 const row) {
        return columns[column][row];
    }

    f32 const& Mat2::operator()(i32 const column, i32 const row) const {
        return columns[column][row];
    }

    f32* Mat2::data()  {
        return (f32*)columns;
    }

    f32 const* Mat2::data() const {
        return (f32 const*)columns;
    }

    Mat2& Mat2::operator+=(f32 const a) {
        columns[0] += a;
        columns[1] += a;
        return *this;
    }

    Mat2& Mat2::operator-=(f32 const a) {
        columns[0] -= a;
        columns[1] -= a;
        return *this;
    }

    Mat2& Mat2::operator*=(f32 const a) {
        columns[0] *= a;
        columns[1] *= a;
        return *this;
    }

    Mat2& Mat2::operator/=(f32 const a) {
        columns[0] /= a;
        columns[1] /= a;
        return *this;
    }

    Mat2& Mat2::operator+=(Mat2 const& m) {
        columns[0] += m.columns[0];
        columns[1] += m.columns[1];
        return *this;
    }

    Mat2& Mat2::operator-=(Mat2 const& m) {
        columns[0] -= m.columns[0];
        columns[1] -= m.columns[1];
        return *this;
    }

    Mat2& Mat2::operator*=(Mat2 const& rhs) {
        Mat2 const lhs = *this;
        for (i32 i = 0; i < 2; ++i) {
            (*this)[i][0] = rhs[i][0] * lhs[0][0] + rhs[i][1] * lhs[1][0];
            (*this)[i][1] = rhs[i][0] * lhs[0][1] + rhs[i][1] * lhs[1][1];
        }
        return *this;
    }

    Mat2 operator+(Mat2 m, f32 const a) {
        m += a;
        return m;
    }

    Mat2 operator-(Mat2 m, f32 const a) {
        m -= a;
        return m;
    }

    Mat2 operator*(Mat2 m, f32 const a) {
        m *= a;
        return m;
    }

    Mat2 operator/(Mat2 m, f32 const a) {
        m /= a;
        return m;
    }

    Mat2 operator+(Mat2 lhs, Mat2 const& rhs) {
        lhs += rhs;
        return lhs;
    }

    Mat2 operator-(Mat2 lhs, Mat2 const& rhs) {
        lhs -= rhs;
        return lhs;
    }

    Mat2 operator*(Mat2 lhs, Mat2 const& rhs) {
        lhs *= rhs;
        return lhs;
    }

    Vec2 operator*(Mat2 const& lhs, Vec2 const& rhs) {
        Vec2 r;
        r[0] = rhs[0] * lhs[0][0] + rhs[1] * lhs[1][0];
        r[1] = rhs[0] * lhs[0][1] + rhs[1] * lhs[1][1];
        return r;
    }

    Mat2 transpose(Mat2 m) {
        detail::swap(m[1][0], m[0][1]);
        return m;
    }

    f32 determinant(Mat2 const& m) {
        return m[0][0] * m[1][1] - m[1][0] * m[0][1];
    }

    Mat2 adjugate(Mat2 const& m) {
        return {{m[1][1], -m[0][1]}, {-m[1][0], m[0][0]}};
    }

    Mat2 inverse(Mat2 const& m) {
        return adjugate(m) / determinant(m);
    }

    void swap(Mat2& m1, Mat2& m2) {
        swap(m1[0], m2[0]);
        swap(m1[1], m2[1]);
    }
}
