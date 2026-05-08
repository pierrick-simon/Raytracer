/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** a
*/

#ifndef PRIMITIVECYLINDER_HPP
    #define PRIMITIVECYLINDER_HPP

    #include <memory>
    #include "IObject.hpp"
    #include "Material.hpp"
    #include "Vector3.hpp"

namespace RayTracer {
    class PrimitiveCylinder : public IObject {
    public:
        PrimitiveCylinder(const Maths::Point3D &origin, double radius,
            std::optional<double> height, Material const &Material);

        std::optional<HitInfo> hits(const Ray &ray) override;
        HitInfo fillHitInfo(const Ray &ray, double t) const;
        void hitCaps(Ray const &ray, std::optional<double> &bestT) const;
        std::optional<double> hitSurface(const Ray &ray) const;
        Maths::Vector3D cylNormal(Maths::Vector3D p) const;
        HitInfo fillHitInfinite(const Ray &ray, double t) const;
        std::optional<HitInfo> hitsInfinite(const Ray &ray) const;
        std::optional<HitInfo> hitsCylinder(const Ray &ray) const;

        [[nodiscard]] const Maths::Point3D &getOrigin() const;
        [[nodiscard]] Maths::Point3D &getOrigin();

        [[nodiscard]] double getRadius() const;
        [[nodiscard]] std::optional<double> getHeight() const;

    private:
        Maths::Point3D _origin;
        double _radius;
        std::optional<double> _height;
        Material _material;
    };
};

#endif
