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
        Vector3() : Matrix<1, 3, Type>({static_cast<Type>(0), static_cast<Type>(0), static_cast<Type>(0)}) {}

        Vector3(Type x, Type y, Type z);

        Vector3(const Matrix<1, 3, Type> &matrix);

        Vector3 &operator=(const Matrix<1, 3, Type> &matrix);

        const Type &getX() const;

        Type &getX();

        const Type &getY() const;

        Type &getY();

        const Type &getZ() const;

        Type &getZ();
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
