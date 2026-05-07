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

    template<typename Type>
    class Vector3 : public Matrix<1, 3, Type> {
    public:
        Vector3(Type x, Type y, Type z);

        Vector3(const Matrix<1, 3, Type> &matrix);

        Vector3 &operator=(const Matrix<1, 3, Type> &matrix);

        const Type &getX() const;

        Type &getX();

        const Type &getY() const;

        Type &getY();

        const Type &getZ() const;

        Type &getZ();

        [[nodiscard]] double length() const
        {
            double sum = 0;

            for (size_t i = 0; i < 3; ++i)
                sum += (*this)(0, i);

            return std::sqrt(sum);
        }

        [[nodiscard]] Vector3 normalized() const
        {
            Vector3 normalized = *this;
            double length = this->length();

            normalized /= length;
            return normalized;
        }

        [[nodiscard]] double distance(const Vector3 &rhs) const
        {
            return distance(*this, rhs);
        }

        [[nodiscard]] double dot(const Vector3 &rhs) const
        {
            return this->x * rhs.x + this->y * rhs.y + this->
                   z * rhs.z;
        }

        [[nodiscard]] double getAngle(const Vector3 &other) const
        {
            double angle = this->dot(other) / (this->length() * other.length());

            return acos(angle);
        }

        [[nodiscard]] Vector3 crossProduct(const Vector3 &rhs) const
        {
            return Vector3(
                this->getY() * rhs.getZ() - this->getZ() * rhs.getY(),
                this->getZ() * rhs.getX() - this->getX() * rhs.getZ(),
                this->getX() * rhs.getY() - this->getY() * rhs.getX()
            );
        }

        Vector3 lerp(const Vector3 &min,
            const Vector3 &max,
            double t)
        {
            return Vector3(
                std::lerp(min.x, max.x, t),
                std::lerp(min.y, max.y, t),
                std::lerp(min.z, max.z, t)
            );
        }

        Vector3 clampedLerp(const Vector3 &min,
            const Vector3 &max, double t)
        {
            return lerp(min, max, std::clamp(t, 0.0, 1.0));
        }
    };

    template<typename Type>
    Vector3<Type>::Vector3(Type x, Type y, Type z) :
        Matrix<1, 3, Type>({x, y, z})
    {
    }

    template<typename Type>
    Vector3<Type>::Vector3(const Matrix<1, 3, Type> &matrix) :
        Matrix<1, 3, Type>(matrix.getMatrix())
    {
    }

    template<typename Type>
    Vector3<Type> &Vector3<Type>::operator=(const Matrix<1, 3, Type> &matrix)
    {
        if (*this == matrix)
            return *this;
        this->_matrix = matrix.getMatrix();
        return *this;
    }

    template<typename Type>
    const Type &Vector3<Type>::getX() const
    {
        return (*this)(0, 0);
    }

    template<typename Type>
    Type &Vector3<Type>::getX()
    {
        return (*this)(0, 0);
    }

    template<typename Type>
    const Type &Vector3<Type>::getY() const
    {
        return (*this)(0, 1);
    }

    template<typename Type>
    Type &Vector3<Type>::getY()
    {
        return (*this)(0, 1);
    }

    template<typename Type>
    const Type &Vector3<Type>::getZ() const
    {
        return (*this)(0, 2);
    }

    template<typename Type>
    Type &Vector3<Type>::getZ()
    {
        return (*this)(0, 2);
    }

    using Vector3D = Vector3<double>;
    using RGB = Vector3<unsigned char>;
    using Vector3U = Vector3<unsigned int>;
    using Vector3I = Vector3<int>;
}

#endif
