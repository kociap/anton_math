#pragma once

#include <anton/types.hpp>
#include <anton/math/vec2.hpp>

namespace anton::math {
    // Mat2
    // Column major matrix with row major layout.
    //
    struct Mat2 {
    public:
        static Mat2 const zero;
        static Mat2 const identity;

        Mat2();
        Mat2(Vec2 const& a, Vec2 const& b);
        explicit Mat2(f32 const* p);

        [[nodiscard]] Vec2& operator[](i32 column);
        [[nodiscard]] Vec2 const& operator[](i32 column) const;

        [[nodiscard]] f32& operator()(i32 column, i32 row);
        [[nodiscard]] f32 const& operator()(i32 column, i32 row) const;

        [[nodiscard]] f32* data();
        [[nodiscard]] f32 const* data() const;

        Mat2& operator+=(f32 a);
        Mat2& operator-=(f32 a);
        Mat2& operator*=(f32 a);
        Mat2& operator/=(f32 a);

        Mat2& operator+=(Mat2 const& m);
        Mat2& operator-=(Mat2 const& m);
        Mat2& operator*=(Mat2 const& rhs);

    private:
        Vec2 columns[2];
    };

    [[nodiscard]] Mat2 operator+(Mat2 m, f32 a);
    [[nodiscard]] Mat2 operator-(Mat2 m, f32 a);
    [[nodiscard]] Mat2 operator*(Mat2 m, f32 a);
    [[nodiscard]] Mat2 operator/(Mat2 m, f32 a);
    [[nodiscard]] Mat2 operator+(Mat2 lhs, Mat2 const& rhs);
    [[nodiscard]] Mat2 operator-(Mat2 lhs, Mat2 const& rhs);
    [[nodiscard]] Mat2 operator*(Mat2 lhs, Mat2 const& rhs);
    [[nodiscard]] Vec2 operator*(Mat2 const& lhs, Vec2 const& rhs);

    [[nodiscard]] Mat2 transpose(Mat2 m);

    [[nodiscard]] f32 determinant(Mat2 const& m);

    [[nodiscard]] Mat2 adjugate(Mat2 const& m);

    [[nodiscard]] Mat2 inverse(Mat2 const& m);

    void swap(Mat2& m1, Mat2& m2);
} // namespace anton::math
