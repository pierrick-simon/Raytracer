/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#include <iomanip>
#include <iostream>
#include <criterion/criterion.h>

#include "Point3.hpp"
#include "Quaternion.hpp"

template<typename Type>
static bool pointEq(const Maths::Point3<Type> &rhs, const Maths::Point3<Type> &lhs, auto epsilon)
{
    return std::abs(rhs.getX() - lhs.getX()) <= epsilon
        && std::abs(rhs.getY() - lhs.getY()) <= epsilon
        && std::abs(rhs.getZ() - lhs.getZ()) <= epsilon;
}

Test(quaternion, pointRotation)
{
    Maths::Quaternion rotation = Maths::Quaternion::fromEulerDegrees(0, 0, -90);

    Maths::Point3D point{-1, -1, 1};

    point = rotation * point;
    cr_assert(pointEq(point, Maths::Point3D(1, -1, 1), 1e-6));
}
