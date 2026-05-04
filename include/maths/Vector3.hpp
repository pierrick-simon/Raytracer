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
    #include <ostream>

    #define TORAD(X) (X * (M_PI / 180.0))

namespace Maths {

    template<typename Type>
    class Point3;

    template<typename Type>
    class Vector3 {
    public:
        constexpr Vector3() = default;

        constexpr Vector3(Type x, Type y, Type z) :
            x(x),
            y(y),
            z(z)
        {
        }

        constexpr Vector3(const Point3<Type> &p):
            x(p.x),
            y(p.y),
            z(p.z)
        {
        }

        constexpr Vector3(const Point3<Type> &p1,
            const Point3<Type> &p2):
            x(p2.x - p1.x),
            y(p2.y - p1.y),
            z(p2.z - p1.z)
        {
        }

        Vector3 operator+(const Vector3 &other) const;

        Vector3 operator+(const Type &other) const;

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

        // used to rotate vector with yaw, pitch and roll 
        void operator[](const Vector3 &other);


        void setPosition(Type x, Type y, Type z);

        [[nodiscard]] double length() const;

        [[nodiscard]] Vector3 normalized() const;

        [[nodiscard]] double distance(const Vector3 &rhs) const;

        [[nodiscard]] double dot(const Vector3 &rhs) const;

        [[nodiscard]] Vector3 crossProduct(Vector3 const &rhs) const;

        static double distance(const Vector3 &lhs, const Vector3 &rhs);

        static Vector3 lerp(const Vector3 &min, const Vector3 &max, double t);
        static Vector3 clampedLerp(const Vector3 &min, const Vector3 &max, double t);

        [[nodiscard]] double getAngle(const Vector3 &other) const;

        Type x;
        Type y;
        Type z;
    };

    template<typename Type>
    Vector3<Type> Vector3<Type>::operator+(const Vector3 &other) const
    {
        return Vector3<Type>(this->x + other.x,
            this->y + other.y,
            this->z + other.z);
    }

    template<typename Type>
    Vector3<Type> Vector3<Type>::operator+(const Type &other) const
    {
        return Vector3<Type>(this->x + other,
            this->y + other,
            this->z + other);
    }

    template<typename Type>
    Vector3<Type> Vector3<Type>::operator-(const Vector3 &other) const
    {
        return Vector3<Type>(this->x - other.x,
            this->y - other.y,
            this->z - other.z);
    }

    template<typename Type>
    Vector3<Type> Vector3<Type>::operator*(const Vector3 &other) const
    {
        return Vector3<Type>(this->x * other.x,
            this->y * other.y,
            this->z * other.z);
    }

    template<typename Type>
    Vector3<Type> Vector3<Type>::operator/(const Vector3 &other) const
    {
        return Vector3<Type>(this->x / other.x,
            this->y / other.y,
            this->z / other.z);
    }

    template<typename Type>
    Vector3<Type> Vector3<Type>::operator*(double m) const
    {
        return Vector3<Type>(this->x * m,
            this->y * m,
            this->z * m);
    }

    template<typename Type>
    Vector3<Type> Vector3<Type>::operator/(double m) const
    {
        return Vector3<Type>(this->x / m,
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
    Vector3<Type> Vector3<Type>::crossProduct(const Vector3 &rhs) const
    {
        return Vector3(
            y * rhs.z - z * rhs.y,
            z * rhs.x - x * rhs.z,
            x * rhs.y - y * rhs.x
        );
    }

    template<typename Type>
    double Vector3<Type>::distance(const Vector3 &lhs, const Vector3 &rhs)
    {
        Vector3 delta = rhs - lhs;

        return delta.length();
    }

    template<typename Type>
    Vector3<Type> Vector3<Type>::lerp(const Vector3 &min, const Vector3 &max,
        double t)
    {
        return Vector3(
                std::lerp(min.x, max.x, t),
                std::lerp(min.y, max.y, t),
                std::lerp(min.z, max.z, t)
            );
    }

    template<typename Type>
    Vector3<Type> Vector3<Type>::clampedLerp(const Vector3 &min,
        const Vector3 &max, double t)
    {
        return lerp(min, max, std::clamp(t, 0.0, 1.0));
    }

    template<typename Type>
    double Vector3<Type>::getAngle(const Vector3 &other) const
    {
        double angle = this->dot(other) / (this->length() * other.length());

        return acos(angle);
    }

    using Vector3D = Vector3<double>;
    using RGB = Vector3<unsigned char>;
    using Vector3U = Vector3<unsigned int>;
    using Vector3I = Vector3<int>;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Maths::Vector3<T> &v) {
    os << "(" << v.x << ";" << v.y << ";" << v.z << ")";
    return os;
}

#endif
