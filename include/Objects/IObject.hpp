/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#ifndef IOBJECT_HPP
    #define IOBJECT_HPP
    #include <optional>
    #include "Point3.hpp"
    #include "Ray.hpp"

namespace RayTracer {
    struct HitInfo {
        Maths::Point3D hitPos;
        Maths::Vector3D impactNormal;
        double hitDist;
    };

    class IObject {
    public:
        virtual ~IObject() = default;

        virtual std::optional<HitInfo> hits(Ray &) = 0;
    };
}

#endif //IOBJECT_HPP