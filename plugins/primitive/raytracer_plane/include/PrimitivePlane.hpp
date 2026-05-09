/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** a
*/

#ifndef PRIMITIVEPLANE_HPP
    #define PRIMITIVEPLANE_HPP

    #include <memory>
    #include <unordered_map>
    #include <string>
    #include "IObject.hpp"
    #include "Vector3.hpp"

namespace RayTracer {
    class PrimitivePlane : public IObject {
    public:
        
        enum class Axis {
            X,
            Y,
            Z
        };

        PrimitivePlane(Axis axis, double pos, Material material);

        std::optional<HitInfo> hits(const Ray &ray) override;

        static std::unordered_map<std::string, Axis> getAxisName();

        [[nodiscard]] Axis getAxis() const;
        [[nodiscard]] double getPos() const;

    private:
        Maths::Vector3D getNormal(double);

        Axis _axis;
        double _pos;
        Material _material;
        Maths::Vector3D _normal;

        static const std::unordered_map<std::string, Axis> _axisName;
    };
};

#endif
