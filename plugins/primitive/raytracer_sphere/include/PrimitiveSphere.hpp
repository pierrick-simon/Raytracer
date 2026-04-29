/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** a
*/

#ifndef PRIMITIVESPHERE_HPP
    #define PRIMITIVESPHERE_HPP

    #include "IObject.hpp"

namespace RayTracer {
    class PrimitiveSphere : public IObject {
    public:
        PrimitiveSphere(const Maths::Point3D &origin, float radius, Maths::RGB color);

        PrimitiveSphere();

        std::optional<HitInfo> hits(Ray &ray) override;

        void setX(float x);

        void setY(float y);

        void setZ(float z);

        void setOrigin(const Maths::Point3D &newOrigin);

        void setRadius(float radius);

        void setColor(Maths::RGB color);

        [[nodiscard]] const Maths::Point3D &getOrigin() const;
        [[nodiscard]] Maths::Point3D &getOrigin();

        [[nodiscard]] float getRadius() const;

        [[nodiscard]] Maths::RGB getColor() const;

    private:
        Maths::Point3D _origin;
        float _radius;
        int _x = 0;
        int _y = 0;
        int _z = 0;
        std::size_t _r = 0;
        Maths::RGB _color;
    };
};

#endif
