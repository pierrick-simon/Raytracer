/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#ifndef RAY_HPP
    #define RAY_HPP
    
    #include "Vector.hpp"
    #include "Point.hpp"

namespace RayTracer {
    class Ray {
        public:
            Maths::Point3D origin;
            Maths::Vector3D direction;
    };
}

#endif //RAY_HPP