/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** a
*/

#ifndef PRIMITIVESPHERE_HPP
    #define PRIMITIVESPHERE_HPP

    #include <memory>
    #include "IObject.hpp"
    #include "Material.hpp"
    #include "Vector.hpp"

namespace RayTracer {
    class PrimitiveSphere : public IObject {
    public:
        PrimitiveSphere(const Maths::Point3D &origin,
            double radius, Material Material);

        std::optional<HitInfo> hits(const Ray &ray) override;

        [[nodiscard]] const Maths::Point3D &getOrigin() const;
        [[nodiscard]] Maths::Point3D &getOrigin();

        [[nodiscard]] double getRadius() const;

    private:

        HitInfo computeHitInfos(const Ray &, double) const noexcept;
        double solveQuadratic(double a, double b,
            double c, double delta) noexcept;

        Maths::Point3D _origin;
        double _radius;
        Material _material;
    };
};

#endif
