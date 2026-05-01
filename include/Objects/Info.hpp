/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Info
*/

#ifndef INFO_HPP
    #define INFO_HPP

    #include "Vector3.hpp"
    #include "Point3.hpp"
    #include "Ray.hpp"

namespace RayTracer {
    struct ScatterInfo {
        Ray scattered;
        Maths::RGB color;
    };

    struct HitInfo {
        Maths::Point3D hitPos;
        Maths::Vector3D impactNormal;
    };
}

#endif
