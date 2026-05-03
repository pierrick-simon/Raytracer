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
    #include "Vector3.hpp"

namespace RayTracer {
    class Pyramid : public IObject {
    public:
        Pyramid(const Maths::Point3D &origin, double height,
            double width, double length, Maths::RGB color);

        std::optional<HitInfo> hits(Ray &ray) override;

        [[nodiscard]] const Maths::Point3D &getOrigin() const;
        [[nodiscard]] Maths::Point3D &getOrigin();
        [[nodiscard]] Maths::RGB getColor() const;
        [[nodiscard]] double getHeight() const;
        [[nodiscard]] double getWidth() const;
        [[nodiscard]] double getLength() const;

    private:
        Maths::Point3D _origin;
        double _height;
        double _width;
        double _length;
        Maths::RGB _color;
        TriangleShape _pyramid;
    };
};

#endif