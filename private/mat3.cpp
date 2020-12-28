#include <anton/math/mat3.hpp>
#include <anton/math/mat4.hpp>
#include <detail/utility.hpp>

namespace anton::math {
    Mat3 const Mat3::zero = Mat3();
    Mat3 const Mat3::identity = Mat3({1, 0, 0}, {0, 1, 0}, {0, 0, 1});

    Mat3::Mat3(): columns{} {}
    Mat3::Mat3(Vec3 const& a, Vec3 const& b, Vec3 const& c): columns{a, b, c} {}
    Mat3::Mat3(Mat4 const& mat): columns{Vec3(mat[0]), Vec3(mat[1]), Vec3(mat[2])} {}
    Mat3::Mat3(f32 const* const p): columns{Vec3{p}, Vec3{p + 3}, Vec3{p + 6}} {}

    Vec3& Mat3::operator[](i32 column) {
        return columns[column];
    }

    Vec3 const& Mat3::operator[](i32 column) const {
        return columns[column];
    }

    f32& Mat3::operator()(i32 const column, i32 const row) {
        return columns[column][row];
    }

    f32 const& Mat3::operator()(i32 const column, i32 const row) const {
        return columns[column][row];
    }

    f32* Mat3::data()  {
        return (f32*)columns;
    }

    f32 const* Mat3::data() const {
        return (f32 const*)columns;
    }

    Mat3& Mat3::operator+=(f32 const a) {
        columns[0] += a;
        columns[1] += a;
        columns[2] += a;
        return *this;
    }

    Mat3& Mat3::operator-=(f32 const a) {
        columns[0] -= a;
        columns[1] -= a;
        columns[2] -= a;
        return *this;
    }

    Mat3& Mat3::operator*=(f32 const a) {
        columns[0] *= a;
        columns[1] *= a;
        columns[2] *= a;
        return *this;
    }

    Mat3& Mat3::operator/=(f32 const a) {
        columns[0] /= a;
        columns[1] /= a;
        columns[2] /= a;
        return *this;
    }

    Mat3& Mat3::operator+=(Mat3 const& m) {
        columns[0] += m.columns[0];
        columns[1] += m.columns[1];
        columns[2] += m.columns[2];
        return *this;
    }

    Mat3& Mat3::operator-=(Mat3 const& m) {
        columns[0] -= m.columns[0];
        columns[1] -= m.columns[1];
        columns[2] -= m.columns[2];
        return *this;
    }

    Mat3& Mat3::operator*=(Mat3 const& rhs) {
        Mat3 const lhs = *this;
        for (i32 i = 0; i < 3; ++i) {
            (*this)[i][0] = rhs[i][0] * lhs[0][0] + rhs[i][1] * lhs[1][0] + rhs[i][2] * lhs[2][0];
            (*this)[i][1] = rhs[i][0] * lhs[0][1] + rhs[i][1] * lhs[1][1] + rhs[i][2] * lhs[2][1];
            (*this)[i][2] = rhs[i][0] * lhs[0][2] + rhs[i][1] * lhs[1][2] + rhs[i][2] * lhs[2][2];
        }
        return *this;
    }

    Mat3 operator+(Mat3 m, f32 a) {
        m += a;
        return m;
    }

    Mat3 operator-(Mat3 m, f32 a) {
        m -= a;
        return m;
    }

    Mat3 operator*(Mat3 m, f32 a) {
        m *= a;
        return m;
    }

    Mat3 operator/(Mat3 m, f32 a) {
        m /= a;
        return m;
    }

    Mat3 operator+(Mat3 lhs, Mat3 const& rhs) {
        lhs += rhs;
        return lhs;
    }

    Mat3 operator-(Mat3 lhs, Mat3 const& rhs) {
        lhs -= rhs;
        return lhs;
    }

    Mat3 operator*(Mat3 lhs, Mat3 const& rhs) {
        lhs *= rhs;
        return lhs;
    }

    Vec3 operator*(Mat3 const& lhs, Vec3 const& rhs) {
        Vec3 r;
        r[0] = rhs[0] * lhs[0][0] + rhs[1] * lhs[1][0] + rhs[2] * lhs[2][0];
        r[1] = rhs[0] * lhs[0][1] + rhs[1] * lhs[1][1] + rhs[2] * lhs[2][1];
        r[2] = rhs[0] * lhs[0][2] + rhs[1] * lhs[1][2] + rhs[2] * lhs[2][2];
        return r;
    }

    Mat3 transpose(Mat3 m) {
        detail::swap(m[0][1], m[1][0]);
        detail::swap(m[0][2], m[2][0]);
        detail::swap(m[1][2], m[2][1]);
        return m;
    }

    static f32 _determinant2x2(f32 m00, f32 m01, f32 m10, f32 m11) {
        return m00 * m11 - m01 * m10;
    }

    f32 determinant(Mat3 const& m) {
        return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) - 
               m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
               m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    }

    Mat3 adjugate(Mat3 const& m) {
        f32 m00 = _determinant2x2(m[1][1], m[1][2], m[2][1], m[2][2]);
        f32 m01 = _determinant2x2(m[1][0], m[1][2], m[2][0], m[2][2]);
        f32 m02 = _determinant2x2(m[1][0], m[1][1], m[2][0], m[2][1]);

        f32 m10 = _determinant2x2(m[0][1], m[0][2], m[2][1], m[2][2]);
        f32 m11 = _determinant2x2(m[0][0], m[0][2], m[2][0], m[2][2]);
        f32 m12 = _determinant2x2(m[0][0], m[0][1], m[2][0], m[2][1]);

        f32 m20 = _determinant2x2(m[0][1], m[0][2], m[1][1], m[1][2]);
        f32 m21 = _determinant2x2(m[0][0], m[0][2], m[1][0], m[1][2]);
        f32 m22 = _determinant2x2(m[0][0], m[0][1], m[1][0], m[1][1]);
        return Mat3(
            {m00, -m10, m20}, 
            {-m01, m11, -m21}, 
            {m02, -m12, m22});
    }

    Mat3 inverse(Mat3 const& m) {
        return adjugate(m) / determinant(m);
    }

    void swap(Mat3& m1, Mat3& m2) {
        swap(m1[0], m2[0]);
        swap(m1[1], m2[1]);
        swap(m1[2], m2[2]);
    }
}
