/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Material
*/

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Vector3.hpp"
#include "Info.hpp"

namespace RayTracer {

    class Material {
        public:
            class Builder {
                public:
                    Builder() = default;

                    Builder &color(Maths::RGB color);
                    Builder &metallic(double metallic);
                    Builder &specular(double specular);
                    Builder &roughness(double roughness);
                    Builder &opacity(double opacity);

                    Material build() const {return Material(*this);}

        private:
            friend class Material;
            Maths::RGB _color = Maths::RGB(255, 255, 255);
            double _metallic = 0;
            double _specular = 0;
            double _roughness = 0;
            double _opacity = 1;
        };

        explicit Material(Builder const &builder);

        void scatter(Ray &ray, HitInfo &info);

    private:
        Maths::Vector3D _colorPercentage;
        double _metallic;
        double _specular;
        double _roughness;
        double _opacity;
    };

}

#endif
