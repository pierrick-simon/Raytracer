/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** a
*/

#ifndef PRIMITIVESPHERE_HPP
    #define PRIMITIVESPHERE_HPP

    #include "ILightSource.hpp"
    #include "Vector3.hpp"

namespace RayTracer {
    class PointLight : public ILightSource {
    public:
        PointLight(const Maths::Point3D &pos, Maths::RGB color, double falloutDistance);

        Maths::RGB getLightAmount(const Ray &) override;
    private:
        Maths::Point3D _pos;
        Maths::RGB _color;
        double falloutDistance;
    };
}

#endif
