/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Material
*/

#ifndef MATERIAL_HPP
    #define MATERIAL_HPP

    #include "Vector3.hpp"
    #include "Ray.hpp"

namespace RayTracer {

    struct HitInfo;

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

                    [[nodiscard]] Maths::RGB getColor() const {return _color;}
                    [[nodiscard]] double getMetallic() const {return _metallic;}
                    [[nodiscard]] double getSpecular() const {return _specular;}
                    [[nodiscard]] double getRoughness() const {return _roughness;}
                    [[nodiscard]] double getOpacity() const {return _opacity;}

                private:
                    Maths::RGB _color;
                    double _metallic;
                    double _specular;
                    double _roughness;
                    double _opacity;
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
