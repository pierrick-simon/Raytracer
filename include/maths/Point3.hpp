/*
** EPITECH PROJECT, 2026
** BS_RayTracer
** File description:
** DESCRIPTION
*/

#ifndef POINT3_HPP
    #define POINT3_HPP

    #include <cmath>

namespace Maths {
    template<typename Type>
    class Vector3;

    template<typename Type>
    class Point3 {
    public:
        Point3() = default;

        Point3(Type x, Type y, Type z);

        Point3(const Point3<Type> &vec);
        
        Point3(const Vector3<Type> &vec);

        Point3 operator+(const Point3<Type> &other) const;

        Point3 operator+(const Type &other) const;

        Point3 operator-(const Point3<Type> &other) const;

        Point3 operator*(const Point3<Type> &other) const;

        Point3 operator/(const Point3<Type> &other) const;

        Point3 &operator+=(const Point3<Type> &other);

        Point3 &operator-=(const Point3<Type> &other);

        Point3 &operator*=(const Point3<Type> &other);

        Point3 &operator/=(const Point3<Type> &other);

        bool operator==(const Point3 &other) const;

        bool operator!=(const Point3 &other) const;
        
        void setPosition(Type x, Type y, Type z);

        [[nodiscard]] double length() const;

        [[nodiscard]] double distance(const Point3 &rhs) const;

        static double distance(const Point3 &lhs, const Point3 &rhs);

        Type x;
        Type y;
        Type z;
    };

    template<typename Type>
    Point3<Type>::Point3(Type x, Type y, Type z) :
        x(x),
        y(y),
        z(z)
    {
    }

    template<typename Type>
    Point3<Type>::Point3(const Point3<Type> &vec) :
        x(vec.x),
        y(vec.y),
        z(vec.z)
    {
    }

    template<typename Type>
    Point3<Type>::Point3(const Vector3<Type> &point) :
        x(point.x),
        y(point.y),
        z(point.z)
    {
    }

    template<typename Type>
    Point3<Type> Point3<Type>::operator+(const Point3<Type> &other) const
    {
        return Point3<Type>(this->x + other.x,
            this->y + other.y,
            this->z + other.z);
    }

    template<typename Type>
    Point3<Type> Point3<Type>::operator+(const Type &other) const
    {
        return Point3<Type>(this->x + other,
            this->y + other,
            this->z + other);
    }

    template<typename Type>
    Point3<Type> Point3<Type>::operator-(const Point3<Type> &other) const
    {
        return Point3<Type>(this->x - other.x,
            this->y - other.y,
            this->z - other.z);
    }

    template<typename Type>
    Point3<Type> Point3<Type>::operator*(const Point3<Type> &other) const
    {
        return Point3<Type>(this->x * other.x,
            this->y * other.y,
            this->z * other.z);
    }

    template<typename Type>
    Point3<Type> Point3<Type>::operator/(const Point3<Type> &other) const
    {
        return Point3<Type>(this->x / other.x,
            this->y / other.y,
            this->z / other.z);
    }

    template<typename Type>
    Point3<Type> &Point3<Type>::operator+=(const Point3<Type> &other)
    {
        this->x = this->x + other.x;
        this->y = this->y + other.y;
        this->z = this->z + other.z;
        return *this;
    }

    template<typename Type>
    Point3<Type> &Point3<Type>::operator-=(const Point3<Type> &other)
    {
        this->x = this->x - other.x;
        this->y = this->y - other.y;
        this->z = this->z - other.z;
        return *this;
    }

    template<typename Type>
    Point3<Type> & Point3<Type>::operator*=(const Point3<Type> &other)
    {
        this->x = this->x * other.x;
        this->y = this->y * other.y;
        this->z = this->z * other.z;
        return *this;
    }

    template<typename Type>
    Point3<Type> & Point3<Type>::operator/=(const Point3<Type> &other)
    {
        this->x = this->x / other.x;
        this->y = this->y / other.y;
        this->z = this->z / other.z;
        return *this;
    }

    template<typename Type>
    bool Point3<Type>::operator==(const Point3 &other) const
    {
        return this->x == other.x &&
               this->y == other.y &&
               this->z == other.z;
    }

    template<typename Type>
    bool Point3<Type>::operator!=(const Point3 &other) const
    {
        return !(*this == other);
    }

    template<typename Type>
    void Point3<Type>::setPosition(Type x, Type y, Type z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    template<typename Type>
    double Point3<Type>::length() const
    {
        double sum = this->x * this->x +
                     this->y * this->y +
                     this->z * this->z;

        return std::sqrt(sum);
    }

    template<typename Type>
    double Point3<Type>::distance(const Point3 &rhs) const
    {
        return distance(*this, rhs);
    }

    template<typename Type>
    double Point3<Type>::distance(const Point3 &lhs, const Point3 &rhs)
    {
        Point3 delta = rhs - lhs;

        return delta.length();
    }

    using Point3D = Point3<double>;

} // Math

#endif
