/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#ifndef PRIMITIVECONE_HPP
    #define PRIMITIVECONE_HPP
    #include "IObject.hpp"
    #include "Material.hpp"
    #include "Vector.hpp"

namespace RayTracer {
    class PrimitiveCone : public IObject {
    public:
        PrimitiveCone(const Maths::Point3D &origin, double radius,
            std::optional<double> height, Material const &Material);

        std::optional<HitInfo> hits(const Ray &ray) override;
        HitInfo fillHitInfo(const Ray &ray, double t) const;

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
