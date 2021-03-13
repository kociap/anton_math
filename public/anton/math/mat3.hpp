#pragma once

#include <anton/types.hpp>
#include <anton/math/vec3.hpp>

namespace anton::math {
    struct Mat4;
    
    // Mat3
    // Column major matrix with row major layout.
    //
    struct Mat3 {
    public:
        static Mat3 const zero;
        static Mat3 const identity;

        Mat3();
        Mat3(Vec3 const& a, Vec3 const& b, Vec3 const& c);
        explicit Mat3(Mat4 const& mat);
        explicit Mat3(f32 const* p);

        [[nodiscard]] Vec3& operator[](i32 column);
        [[nodiscard]] Vec3 const& operator[](i32 column) const;

        [[nodiscard]] f32& operator()(i32 column, i32 row);
        [[nodiscard]] f32 const& operator()(i32 column, i32 row) const;

        [[nodiscard]] f32* data();
        [[nodiscard]] f32 const* data() const;

        Mat3& operator+=(f32 a);
        Mat3& operator-=(f32 a);
        Mat3& operator*=(f32 a);
        Mat3& operator/=(f32 a);

        Mat3& operator+=(Mat3 const& m);
        Mat3& operator-=(Mat3 const& m);
        Mat3& operator*=(Mat3 const& rhs);

    private:
        Vec3 columns[3];
    };

    [[nodiscard]] Mat3 operator+(Mat3 m, f32 a);
    [[nodiscard]] Mat3 operator-(Mat3 m, f32 a);
    [[nodiscard]] Mat3 operator*(Mat3 m, f32 a);
    [[nodiscard]] Mat3 operator/(Mat3 m, f32 a);
    [[nodiscard]] Mat3 operator+(Mat3 lhs, Mat3 const& rhs);
    [[nodiscard]] Mat3 operator-(Mat3 lhs, Mat3 const& rhs);
    [[nodiscard]] Mat3 operator*(Mat3 lhs, Mat3 const& rhs);
    [[nodiscard]] Vec3 operator*(Mat3 const& lhs, Vec3 const& rhs);

    [[nodiscard]] Mat3 transpose(Mat3 m);

    [[nodiscard]] f32 determinant(Mat3 const& m);

    [[nodiscard]] Mat3 adjugate(Mat3 const& m);

    [[nodiscard]] Mat3 inverse(Mat3 const& m);

    void swap(Mat3& m1, Mat3& m2);
} // namespace anton::math
