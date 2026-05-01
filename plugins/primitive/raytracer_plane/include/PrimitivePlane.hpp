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

        PrimitivePlane(Axis axis, double pos,
            std::shared_ptr<IMaterial> material);

        std::optional<HitInfo> hits(Ray &ray) override;
        std::shared_ptr<IMaterial> getIMaterial() override
            {return _material;}

        static const std::unordered_map<std::string, Axis> getAxisName()
            {return _axisName;}

        [[nodiscard]] Axis getAxis() const;
        [[nodiscard]] double getPos() const;

    private:
        Axis _axis;
        double _pos;
        std::shared_ptr<IMaterial> _material;
        
        static const std::unordered_map<std::string, Axis> _axisName;
    };
};

#endif
