/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** a
*/

#ifndef PRIMITIVESPHERE_HPP
    #define PRIMITIVESPHERE_HPP

    #include "ALightSource.hpp"
    #include "Vector.hpp"

namespace RayTracer {
    class SpotLight : public ALightSource {
    public:
        class Builder {
            Builder() = default;
        public:
            static Builder builder();

            [[nodiscard]] Maths::Point3D getPos() const;
            [[nodiscard]] Maths::Vector3D getDirection() const;
            [[nodiscard]] Maths::Color getColor() const;
            [[nodiscard]] double getFalloutDistance() const;
            [[nodiscard]] double getOuterConeAngle() const;
            [[nodiscard]] double getInnerConeAngle() const;

            [[nodiscard]] Builder withPos(const Maths::Point3D &pos) const;
            [[nodiscard]] Builder withDirection(const Maths::Vector3D &dir) const;
            [[nodiscard]] Builder withColor(Maths::Color color) const;
            [[nodiscard]] Builder withFalloutDistance(double falloutDistance) const;
            [[nodiscard]] Builder withOuterConeAngle(double outerAngle) const;
            [[nodiscard]] Builder withInnerConeAngle(double innerAngle) const;

        private:
            Maths::Point3D _pos;
            Maths::Vector3D _direction;
            Maths::Color _color;
            double _falloutDistance;
            double _outerConeAngle;
            double _innerConeAngle;
        };
        SpotLight(const Builder &builder);

        [[nodiscard]] Maths::Color getLightAmount(const Ray &) const override;

    private:
        Maths::Vector3D _direction;
        Maths::Color _color;
        double _falloutDistance;
        double _outerConeAngle;
        double _innerConeAngle;
    };
}

#endif
