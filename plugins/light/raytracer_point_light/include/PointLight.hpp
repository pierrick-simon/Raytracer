/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** a
*/

#ifndef PRIMITIVESPHERE_HPP
    #define PRIMITIVESPHERE_HPP

    #include "ALightSource.hpp"
    #include "Vector3.hpp"

namespace RayTracer {
    class PointLight : public ALightSource {
    public:
        PointLight(const Maths::Point3D &pos, Maths::RGB color, double falloutDistance);

        [[nodiscard]] Maths::RGB getLightAmount(const Ray &) const override;
    private:
        Maths::RGB _color;
        double _falloutDistance;
    };
}

#endif
