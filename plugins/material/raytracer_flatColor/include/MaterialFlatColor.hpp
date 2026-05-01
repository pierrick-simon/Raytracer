/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** MaterialFlatColor
*/

#ifndef MATERIALFLATCOLOR_HPP
    #define MATERIALFLATCOLOR_HPP

    #include "Vector3.hpp"
    #include "IMaterial.hpp"

namespace RayTracer {
    class MaterialFlatColor : public IMaterial {
        public:
            MaterialFlatColor(Maths::RGB color) : _color(color) {};

            std::optional<ScatterInfo> scatter(Ray &, HitInfo &) override;

            [[nodiscard]] Maths::RGB getColor() const {return _color;}

        private:
            Maths::RGB _color;
    };
}

#endif
