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

        Triangle(const std::array<const Maths::Point3D, 3> &points,
            const Material &material,
            std::optional<std::reference_wrapper<const Texture>> texture,
            std::optional<std::array<Maths::Vector3D, 3>> texCoords);

        std::optional<Maths::Color> getTextureColor(
            const Maths::Vector2D &uvPos) const;

        std::optional<HitInfo> createHitInfo(const Ray &ray,
            double t, const Maths::Vector2D &uvPos) const;

        const std::optional<std::array<Maths::Vector3D, 3>> &
        getTexCoords() const noexcept
        {
            return _texCoords;
        }

        std::optional<HitInfo> hits(const Ray &ray) const;

    private:
        std::array<const Maths::Point3D, 3> _points;
        std::optional<std::reference_wrapper<const Texture>> _texture;
        std::optional<std::array<Maths::Vector3D, 3>> _texCoords;
        Material _material;
        const Maths::Vector3D _ab;
        const Maths::Vector3D _ac;
    };
} // RayTracer

#endif
