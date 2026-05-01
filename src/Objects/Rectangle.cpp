/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Rectangle
*/

#include "Point3.hpp"
#include "Rectangle.hpp"

Maths::Point3D RayTracer::Rectangle::pointAt(double u, double v) const noexcept
    {   
        Maths::Point3D p;
        if (u > 1)
            u = 1;
        if (v > 1)
            v = 1;
        if (u < 0)
            u = 0;
        if (v < 0)
            v = 0;
        p.x = (_topSide.x * u) + (_leftSide.x * v) + _origin.x;
        p.y = (_topSide.y * u) + (_leftSide.y * v) + _origin.y;
        p.z = (_topSide.z * u) + (_leftSide.z * v) + _origin.z;
        return p;
    }