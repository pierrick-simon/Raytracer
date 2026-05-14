/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** info
*/

#ifndef INFO_HPP
    #define INFO_HPP

    #include "Point.hpp"
    #include "Material.hpp"

namespace RayTracer {
    struct HitInfo {
        Maths::Point3D hitPos;
        Maths::Vector3D impactNormal;
        double hitDist = 0;
        Material material = Material::Builder().build();
        std::optional<Maths::Color> textureColor; 
    };
}

#endif
