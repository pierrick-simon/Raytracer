/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** Triangle
*/

#ifndef TRIANGLE_HPP
    #define TRIANGLE_HPP

    #include <array>
    #include <optional>
    #include <functional>

    #include "Point.hpp"
    #include "Ray.hpp"
    #include "Info.hpp"
    #include "Texture.hpp"

namespace RayTracer {
    class Triangle {
    public:
        Triangle() = default;
        Triangle(const Maths::Point3D &a, const Maths::Point3D &b,
            const Maths::Point3D &c,
            std::optional<std::reference_wrapper<const Texture>> texture,
            std::optional<std::array<Maths::Vector3D, 3>> texCoords);

        const std::array<Maths::Point3D, 3> &getPoints() const noexcept;

        std::optional<HitInfo> createHitInfo(const Ray &ray, double u, double v,
            double t) const;

        const std::optional<std::array<Maths::Vector3D, 3>> &
        getTexCoords() const noexcept
        {
            return _texCoords;
        }

        std::optional<HitInfo> hits(const Ray &ray) const;

    private:
        std::array<Maths::Point3D, 3> _points;
        std::optional<std::reference_wrapper<const Texture>> _texture;
        std::optional<std::array<Maths::Vector3D, 3>> _texCoords;
        const Maths::Vector3D _ab;
        const Maths::Vector3D _ac;
    };
} // RayTracer

#endif
