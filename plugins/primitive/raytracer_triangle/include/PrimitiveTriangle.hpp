/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#ifndef PRIMITIVETRIANGLE_HPP
    #define PRIMITIVETRIANGLE_HPP

    #include "IObject.hpp"
    #include "Vector3.hpp"

namespace RayTracer {
    class PrimitiveTriangle : public IObject {
    public:
        PrimitiveTriangle(const Maths::Point3D &origin, double height,
            double width, double length, Maths::RGB color);

        std::optional<HitInfo> hits(Ray &ray) override;

        [[nodiscard]] const Maths::Point3D &getOrigin() const;
        [[nodiscard]] Maths::Point3D &getOrigin();
        [[nodiscard]] Maths::RGB getColor() const;

    private:
        Maths::Point3D _origin;
        double _height;
        double _width;
        double _length;
        Maths::RGB _color;
    };
};

#endif