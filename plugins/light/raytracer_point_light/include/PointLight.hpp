/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** a
*/

#ifndef PRIMITIVESPHERE_HPP
    #define PRIMITIVESPHERE_HPP

    #include "ALightSource.hpp"
    #include "Vector.hpp"

namespace RayTracer {
    class PointLight : public ALightSource {
    public:
        PointLight(const Maths::Point3D &pos, Maths::Color color, double falloutDistance);

        [[nodiscard]] Maths::Color getLightAmount(const Ray &) const override;
    private:
        Maths::Color _color;
        double _falloutDistance;
    };
}

#endif
