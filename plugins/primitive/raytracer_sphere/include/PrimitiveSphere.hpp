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
    #include "Vector3.hpp"

namespace RayTracer {
    class PrimitiveSphere : public IObject {
    public:
        PrimitiveSphere(const Maths::Point3D &origin,
            double radius, Material Material);

        std::optional<HitInfo> hits(Ray &ray) override;

        [[nodiscard]] const Maths::Point3D &getOrigin() const;
        [[nodiscard]] Maths::Point3D &getOrigin();

        [[nodiscard]] double getRadius() const;

    private:
        Maths::Point3D _origin;
        double _radius;
        Material _material;
    };
};

#endif
