/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** a
*/

#ifndef PRIMITIVESPHERE_HPP
    #define PRIMITIVESPHERE_HPP

#include "IObject.hpp"

namespace RayTracer {

    class PrimitiveSphere : public IObject {
        public:
            PrimitiveSphere(const Maths::Point3D &origin, float radius):
                _origin(origin),
                _radius(radius)
                {};
            
            PrimitiveSphere():
                _origin(0, 2, 0),
                _radius(0.5)
                {};
            
            std::optional<HitInfo> hits(Ray &);
            Maths::Point3D _origin;
            float _radius;
    };
};

#endif
