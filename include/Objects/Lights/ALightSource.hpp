/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#ifndef ALIGHTSOURCE_HPP
    #define ALIGHTSOURCE_HPP
    #include "ILightSource.hpp"

namespace RayTracer {
    class ALightSource : public ILightSource {
    public:
        explicit ALightSource(const Maths::Point3D &pos);

        [[nodiscard]] Maths::Point3D getPosition() const override;
    protected:
        Maths::Point3D _pos;
    };
} // RayTracer

#endif
