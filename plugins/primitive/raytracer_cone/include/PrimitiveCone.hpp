/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#ifndef PRIMITIVECONE_HPP
    #define PRIMITIVECONE_HPP
    #include <Texture.hpp>

    #include "IObject.hpp"
    #include "Material.hpp"
    #include "Vector.hpp"

namespace RayTracer {
    class PrimitiveCone : public IObject {
    public:
        PrimitiveCone(const Maths::Point3D &origin, double radius,
            std::optional<double> height, Material Material, std::optional<Texture> texture);

        [[nodiscard]] std::optional<HitInfo> hitsInfinite(Ray const & ray) const;

        void getBottomCapBestT(std::optional<double> &bestT, double t,
            double hx,
            double hy) const;

        bool getSlideBestT(std::optional<double> &bestT, double t, double hitZ) const;

        [[nodiscard]] std::optional<HitInfo> hitsCone(Ray const & ray) const;

        std::optional<HitInfo> hits(const Ray &ray) override;

        [[nodiscard]] Maths::Vector3D coneNormal(Maths::Point3D const &point3) const;
        [[nodiscard]] std::optional<double> hitSlide(Ray const &ray, Maths::Vector3D diff,
            double a, double b, double delta) const;
        void hitCap(Ray const &ray, Maths::Vector3D diff, std::optional<double> &bestT) const;
        [[nodiscard]] HitInfo fillHitInfo(const Ray &ray, double t) const;

        [[nodiscard]] const Maths::Point3D &getOrigin() const;
        [[nodiscard]] Maths::Point3D &getOrigin();

        [[nodiscard]] double getRadius() const;
        [[nodiscard]] std::optional<double> getHeight() const;

    private:
        Maths::Point3D _origin;
        double _radius;
        std::optional<double> _height;
        Material _material;
        std::optional<Texture> _texture;
    };
};

#endif
