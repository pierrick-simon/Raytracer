/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#ifndef RAY_HPP
    #define RAY_HPP
    #include "Vector3.hpp"
    #include "Point3.hpp"

namespace RayTracer {
    class Ray {
        Maths::Point3D _origin;
        Maths::Vector3D _direction;
        Maths::RGB _color;
    };
}

#endif //RAY_HPP