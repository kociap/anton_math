#pragma once

#include <anton/types.hpp>
#include <anton/math/vec4.hpp>

namespace anton::math {
    // Mat4
    // Column major matrix with row major layout.
    //
    struct Mat4 {
    public:
        static Mat4 const zero;
        static Mat4 const identity;

        Mat4();
        Mat4(Vec4 const& a, Vec4 const& b, Vec4 const& c, Vec4 const& d);
        explicit Mat4(f32 const* p);

        [[nodiscard]] Vec4& operator[](i32 column);
        [[nodiscard]] Vec4 const& operator[](i32 column) const;

        [[nodiscard]] f32& operator()(i32 column, i32 row);
        [[nodiscard]] f32 const& operator()(i32 column, i32 row) const;

        [[nodiscard]] f32* data();
        [[nodiscard]] f32 const* data() const;

        Mat4& operator+=(f32 a);
        Mat4& operator-=(f32 a);
        Mat4& operator*=(f32 a);
        Mat4& operator/=(f32 a);

        Mat4& operator+=(Mat4 const& m);
        Mat4& operator-=(Mat4 const& m);
        Mat4& operator*=(Mat4 const& rhs);

    private:
        Vec4 columns[4];
    };

    [[nodiscard]] Mat4 operator+(Mat4 m, f32 const a);
    [[nodiscard]] Mat4 operator-(Mat4 m, f32 const a);
    [[nodiscard]] Mat4 operator*(Mat4 m, f32 const a);
    [[nodiscard]] Mat4 operator/(Mat4 m, f32 const a);
    [[nodiscard]] Mat4 operator+(Mat4 lhs, Mat4 const& rhs);
    [[nodiscard]] Mat4 operator-(Mat4 lhs, Mat4 const& rhs);
    [[nodiscard]] Mat4 operator*(Mat4 lhs, Mat4 const& rhs);
    [[nodiscard]] Vec4 operator*(Mat4 const& lhs, Vec4 const& rhs);

    [[nodiscard]] Mat4 transpose(Mat4 mat);

    [[nodiscard]] f32 determinant(Mat4 const& m);

    [[nodiscard]] Mat4 adjugate(Mat4 const& m);

    [[nodiscard]] Mat4 inverse(Mat4 const& m);

    void swap(Mat4& m1, Mat4& m2);
} // namespace anton::math
