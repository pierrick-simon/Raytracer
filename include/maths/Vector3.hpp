/*
** EPITECH PROJECT, 2026
** BS_RayTracer
** File description:
** DESCRIPTION
*/

#ifndef VECTOR3_HPP
    #define VECTOR3_HPP

    #include <cmath>

namespace Maths {
    template<typename Type>
    class Vector3 {
    public:
        constexpr Vector3() = default;

        constexpr explicit Vector3(Type x, Type y, Type z) :
            x(x),
            y(y),
            z(z)
        {
        }

        Vector3 operator+(const Vector3 &other) const;

        Vector3 operator-(const Vector3 &other) const;

        Vector3 operator*(const Vector3 &other) const;

        Vector3 operator/(const Vector3 &other) const;

        Vector3 operator*(double m) const;

        Vector3 operator/(double m) const;

        Vector3 &operator+=(const Vector3 &other);

        Vector3 &operator-=(const Vector3 &other);

        Vector3 &operator*=(const Vector3 &other);

        Vector3 &operator/=(const Vector3 &other);

        Vector3 &operator*=(double m);

        Vector3 &operator/=(double m);

        bool operator==(const Vector3 &other) const;

        bool operator!=(const Vector3 &other) const;

        void setPosition(Type x, Type y, Type z);

        [[nodiscard]] double length() const;

        [[nodiscard]] Vector3 normalized() const;

        [[nodiscard]] double distance(const Vector3 &rhs) const;

        [[nodiscard]] double dot(const Vector3 &rhs) const;

        static double distance(const Vector3 &lhs, const Vector3 &rhs);

        Type x;
        Type y;
        Type z;
    };

    template<typename Type>
    Vector3<Type> Vector3<Type>::operator+(const Vector3 &other) const
    {
        return Vector3D(this->x + other.x,
            this->y + other.y,
            this->z + other.z);
    }

    template<typename Type>
    Vector3<Type> Vector3<Type>::operator-(const Vector3 &other) const
    {
        return Vector3D(this->x - other.x,
            this->y - other.y,
            this->z - other.z);
    }

    template<typename Type>
    Vector3<Type> Vector3<Type>::operator*(const Vector3 &other) const
    {
        return Vector3D(this->x * other.x,
            this->y * other.y,
            this->z * other.z);
    }

    template<typename Type>
    Vector3<Type> Vector3<Type>::operator/(const Vector3 &other) const
    {
        return Vector3D(this->x / other.x,
            this->y / other.y,
            this->z / other.z);
    }

    template<typename Type>
    Vector3<Type> Vector3<Type>::operator*(double m) const
    {
        return Vector3D(this->x * m,
            this->y * m,
            this->z * m);
    }

    template<typename Type>
    Vector3<Type> Vector3<Type>::operator/(double m) const
    {
        return Vector3D(this->x / m,
            this->y / m,
            this->z / m);
    }

    template<typename Type>
    Vector3<Type> &Vector3<Type>::operator+=(const Vector3 &other)
    {
        this->x = this->x + other.x;
        this->y = this->y + other.y;
        this->z = this->z + other.z;
        return *this;
    }

    template<typename Type>
    Vector3<Type> &Vector3<Type>::operator-=(const Vector3 &other)
    {
        this->x = this->x - other.x;
        this->y = this->y - other.y;
        this->z = this->z - other.z;
        return *this;
    }

    template<typename Type>
    Vector3<Type> &Vector3<Type>::operator*=(const Vector3 &other)
    {
        this->x = this->x * other.x;
        this->y = this->y * other.y;
        this->z = this->z * other.z;
        return *this;
    }

    template<typename Type>
    Vector3<Type> &Vector3<Type>::operator/=(const Vector3 &other)
    {
        this->x = this->x / other.x;
        this->y = this->y / other.y;
        this->z = this->z / other.z;
        return *this;
    }

    template<typename Type>
    Vector3<Type> &Vector3<Type>::operator*=(double m)
    {
        this->x = this->x * m;
        this->y = this->y * m;
        this->z = this->z * m;
        return *this;
    }

    template<typename Type>
    Vector3<Type> &Vector3<Type>::operator/=(double m)
    {
        this->x = this->x / m;
        this->y = this->y / m;
        this->z = this->z / m;
        return *this;
    }

    template<typename Type>
    bool Vector3<Type>::operator==(const Vector3 &other) const
    {
        return this->x == other.x &&
               this->y == other.y &&
               this->z == other.z;
    }

    template<typename Type>
    bool Vector3<Type>::operator!=(const Vector3 &other) const
    {
        return !(*this == other);
    }

    template<typename Type>
    void Vector3<Type>::setPosition(Type x, Type y, Type z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    template<typename Type>
    double Vector3<Type>::length() const
    {
        double sum = this->x * this->x +
                     this->y * this->y +
                     this->z * this->z;

        return std::sqrt(sum);
    }

    template<typename Type>
    Vector3<Type> Vector3<Type>::normalized() const
    {
        Vector3 normalized = *this;
        double length = this->length();

        normalized /= length;
        return normalized;
    }

    template<typename Type>
    double Vector3<Type>::distance(const Vector3 &rhs) const
    {
        return distance(*this, rhs);
    }

    template<typename Type>
    double Vector3<Type>::dot(const Vector3 &rhs) const
    {
        return this->x * rhs.x + this->y * rhs.y + this->
               z * rhs.z;
    }

    template<typename Type>
    double Vector3<Type>::distance(const Vector3 &lhs, const Vector3 &rhs)
    {
        Vector3 delta = rhs - lhs;

        return delta.length();
    }

    using Vector3D = Vector3<double>;
    using RGB = Vector3<unsigned char>;
} // bs

#endif
