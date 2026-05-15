/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#ifndef PYRAMID_HPP
    #define PYRAMID_HPP

    #include "TriangleShape.hpp"
    #include "IObject.hpp"
    #include "Vector.hpp"

namespace RayTracer {
    class Pyramid : public IObject {
    public:
        Pyramid(const Maths::Point3D &origin, double height,
            double width, double length, Material material,
            std::optional<Texture> texture = std::nullopt);

        std::optional<HitInfo> hits(Ray const &ray) override;

        [[nodiscard]] const Maths::Point3D &getOrigin() const;
        [[nodiscard]] Maths::Point3D &getOrigin();
        [[nodiscard]] Material getMaterial() const;
        [[nodiscard]] double getHeight() const;
        [[nodiscard]] double getWidth() const;
        [[nodiscard]] double getLength() const;

    private:
        Maths::Point3D _origin;
        double _height;
        double _width;
        double _length;
        Material _material;
        TriangleShape _pyramid;
        std::optional<Texture> _texture;
    };
};

#endif