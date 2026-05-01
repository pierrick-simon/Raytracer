/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** info
*/

#ifndef INFO_HPP
    #define INFO_HPP

    #include "Vector3.hpp"
    #include "Ray.hpp"

namespace RayTracer {
    struct HitInfo {
        Maths::Point3D hitPos;
        Maths::Vector3D impactNormal;
    };
};

#endif
