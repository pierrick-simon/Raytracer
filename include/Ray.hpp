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
        public:
            Maths::Point3D origin;
            Maths::Vector3D direction;
            Maths::Vector3D colorPercentage;
            double strenght;
    };
}

#endif //RAY_HPP