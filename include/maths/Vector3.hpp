/*
** EPITECH PROJECT, 2026
** BS_RayTracer
** File description:
** DESCRIPTION
*/

#ifndef VECTOR3_HPP
    #define VECTOR3_HPP

    #include <algorithm>
    #include <cmath>

    #include "Matrix.hpp"

    #define TORAD(X) (X * (M_PI / 180.0))

namespace Maths {
    template<typename Type>
    class Point3;

    template<std::size_t Dim, typename Type>
    class Vector : public Matrix<Dim, 1, Type> {
    public:
        template<typename... Args>
            requires (sizeof...(Args) == Dim)
        explicit constexpr Vector(Args &&... args) :
            Matrix<Dim, 1, Type>{static_cast<Type>(args)...}
        {
        }

        Vector(const Matrix<Dim, 1, Type> &matrix);

        Vector &operator=(const Matrix<Dim, 1, Type> &matrix);

        const Type &operator[](size_t index) const
        {
            return (*this)(index, 0);
        }

        Type &operator[](size_t index)
        {
            return (*this)(index, 0);
        }

        [[nodiscard]] double norm() const
        {
            double sum = 0;

            for (size_t i = 0; i < Dim; ++i)
                sum += (*this)[i];

            return std::sqrt(sum);
        }

        [[nodiscard]] Vector normalized() const
        {
            Vector normalized = *this;
            double length = this->norm();

            normalized /= length;
            return normalized;
        }

        [[nodiscard]] double distance(const Vector &rhs) const
        {
            Vector delta = *this - delta;
            return delta.norm();
        }

        [[nodiscard]] double dot(const Vector &rhs) const
        {
            double result = 0;

            for (size_t i = 0; i < Dim; ++i)
                result += (*this)[i] * rhs[i];
            return result;
        }

        [[nodiscard]] double getAngle(const Vector &other) const
        {
            double angle = this->dot(other) / (this->norm() * other.norm());

            return acos(angle);
        }

        static Vector lerp(const Vector &min, const Vector &max, double t)
        {
            return min * (1.0 - t) + max * t;
        }

        Vector clampedLerp(const Vector &min,
            const Vector &max, double t)
        {
            return lerp(min, max, std::clamp(t, 0.0, 1.0));
        }

        Vector crossProduct(const Vector &rhs) const
            requires (Dim == 3)
        {
            return Vector(
                (*this)[1] * rhs[2] - (*this)[2] * rhs[1],
                (*this)[2] * rhs[0] - (*this)[0] * rhs[2],
                (*this)[0] * rhs[1] - (*this)[1] * rhs[0]
            );
        }

        const Type &getX() const
            requires (Dim <= 4)
        {
            return (*this)[0];
        }

        Type &getX()
            requires (Dim <= 4)
        {
            return (*this)[0];
        }

        const Type &getY() const
            requires (Dim >= 2 && Dim <= 4)
        {
            return (*this)[1];
        }

        Type &getY()
            requires (Dim >= 2 && Dim <= 4)
        {
            return (*this)[1];
        }

        const Type &getZ() const
            requires (Dim == 3 || Dim == 4)
        {
            return (*this)[2];
        }

        Type &getZ()
            requires (Dim == 3 || Dim == 4)
        {
            return (*this)[2];
        }

        const Type &getW() const
            requires (Dim == 4)
        {
            return (*this)[3];
        }

        Type &getW()
            requires (Dim == 4)
        {
            return (*this)[3];
        }
    };

    template<std::size_t Dim, typename Type>
    Vector<Dim, Type>::Vector(const Matrix<Dim, 1, Type> &matrix) :
        Matrix<Dim, 1, Type>(matrix.getMatrix())
    {
    }

    template<std::size_t Dim, typename Type>
    Vector<Dim, Type> &Vector<Dim, Type>::operator=(
        const Matrix<Dim, 1, Type> &matrix)
    {
        if (*this == matrix)
            return *this;
        this->_matrix = matrix.getMatrix();
        return *this;
    }

    template<typename Type>
    using Vector3 = Vector<3, Type>;

    using Vector3D = Vector3<double>;
    using RGB = Vector3<unsigned char>;
    using Vector3U = Vector3<unsigned int>;
    using Vector3I = Vector3<int>;
}

#endif
