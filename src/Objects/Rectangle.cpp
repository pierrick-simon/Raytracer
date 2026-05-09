/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Rectangle
*/

#include "Point.hpp"
#include "Rectangle.hpp"

Maths::Point3D RayTracer::Rectangle::pointAt(double u, double v) const noexcept
    {
        u = std::clamp(u, 0.0, 1.0);
        v = std::clamp(v, 0.0, 1.0);
        return _topSide * u + _leftSide * v + _origin;
    }