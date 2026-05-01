/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** a
*/

#ifndef PRIMITIVESPHERE_HPP
    #define PRIMITIVESPHERE_HPP

    #include "IObject.hpp"
    #include "Vector3.hpp"

namespace RayTracer {
    class PrimitiveSphere : public IObject {
    public:
        PrimitiveSphere(const Maths::Point3D &origin, double radius, Maths::RGB color);

        std::optional<HitInfo> hits(Ray &ray) override;

        [[nodiscard]] const Maths::Point3D &getOrigin() const;
        [[nodiscard]] Maths::Point3D &getOrigin();

        [[nodiscard]] double getRadius() const;

        [[nodiscard]] Maths::RGB getColor() const;

    private:

        HitInfo computeHitInfos(Ray &, double) noexcept;
        double solveQuadratic(double a, double b,
            double c, double delta) noexcept;

        Maths::Point3D _origin;
        double _radius;
        Maths::RGB _color;
    };
};

#endif
