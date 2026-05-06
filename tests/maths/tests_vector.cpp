/*
** EPITECH PROJECT, 2026
** day10
** File description:
** DESCRIPTION
*/

#include <criterion/criterion.h>

#include "Vector3.hpp"


Test(Vector3, addition)
{
    Maths::Vector3D a(1.0, 2.0, 3.0);
    Maths::Vector3D b(4.0, 5.0, 6.0);

    Maths::Vector3D result = a + b;

    cr_assert_eq(result.getX(), 5.0);
    cr_assert_eq(result.getY(), 7.0);
    cr_assert_eq(result.getZ(), 9.0);
}

Test(Vector3, subtraction)
{
    Maths::Vector3D a(5.0, 7.0, 9.0);
    Maths::Vector3D b(1.0, 2.0, 3.0);

    Maths::Vector3D result = a - b;

    cr_assert_eq(result.getX(), 4.0);
    cr_assert_eq(result.getY(), 5.0);
    cr_assert_eq(result.getZ(), 6.0);
}

Test(Vector3, scalar_multiplication)
{
    Maths::Vector3D v(1.0, -2.0, 3.0);

    Maths::Vector3D result = v * 2.0;

    cr_assert_eq(result.getX(), 2.0);
    cr_assert_eq(result.getY(), -4.0);
    cr_assert_eq(result.getZ(), 6.0);
}

Test(Vector3, length)
{
    Maths::Vector3D v(3.0, 4.0, 0.0);

    double len = v.length();

    cr_assert_float_eq(len, 5.0, 1e-6);
}

Test(Vector3, normalization)
{
    Maths::Vector3D v(0.0, 3.0, 4.0);

    Maths::Vector3D n = v.normalized();

    cr_assert_float_eq(n.getX(), 0.0, 1e-6);
    cr_assert_float_eq(n.getY(), 0.6, 1e-6);
    cr_assert_float_eq(n.getZ(), 0.8, 1e-6);
}

Test(Vector3, dot_product)
{
    Maths::Vector3D a(1.0, 2.0, 3.0);
    Maths::Vector3D b(4.0, -5.0, 6.0);

    double result = a.dot(b);

    cr_assert_eq(result, 12.0);
}

Test(Vector3, cross_product)
{
    Maths::Vector3D a(1.0, 0.0, 0.0);
    Maths::Vector3D b(0.0, 1.0, 0.0);

    Maths::Vector3D result = a.crossProduct(b);

    cr_assert_eq(result.getX(), 0.0);
    cr_assert_eq(result.getY(), 0.0);
    cr_assert_eq(result.getZ(), 1.0);
}

Test(Vector3, distance)
{
    Maths::Vector3D a(0.0, 0.0, 0.0);
    Maths::Vector3D b(0.0, 3.0, 4.0);

    double dist = a.distance(b);

    cr_assert_float_eq(dist, 5.0, 1e-6);
}

Test(Vector3, lerp)
{
    Maths::Vector3D a(0.0, 0.0, 0.0);
    Maths::Vector3D b(10.0, 10.0, 10.0);

    Maths::Vector3D result = Maths::Vector3D::lerp(a, b, 0.5);

    cr_assert_float_eq(result.getX(), 5.0, 1e-6);
    cr_assert_float_eq(result.getY(), 5.0, 1e-6);
    cr_assert_float_eq(result.getZ(), 5.0, 1e-6);
}

Test(Vector3, equality)
{
    Maths::Vector3D a(1.0, 2.0, 3.0);
    Maths::Vector3D b(1.0, 2.0, 3.0);

    cr_assert(a == b);
    cr_assert(!(a != b));
}
