/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Material
*/

#ifndef MATERIAL_HPP
    #define MATERIAL_HPP

    #include <optional>
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
                    Builder &refraction(double refraction);

                    Material build() const {return Material(*this);}

                    [[nodiscard]] Maths::RGB getColor() const {return _color;}
                    [[nodiscard]] double getMetallic() const {return _metallic;}
                    [[nodiscard]] double getSpecular() const {return _specular;}
                    [[nodiscard]] double getRoughness() const {return _roughness;}
                    [[nodiscard]] double getOpacity() const {return _opacity;}
                    [[nodiscard]] double getRefraction() const {return _refraction;}

                private:
                    Maths::RGB _color = Maths::RGB(255, 255, 255);
                    double _metallic;
                    double _specular;
                    double _roughness;
                    double _opacity;
                    double _refraction;
            };

            explicit Material(Builder const &builder);

            Ray reflect(const Ray &ray, const HitInfo &hit) const;
            std::optional<Ray> through(const Ray &ray, const HitInfo &hit) const;
            Ray diffuse(const Ray &ray, const HitInfo &hit) const;

            Ray getReflectRay(const Ray &ray, const HitInfo &hit) const;

            Maths::Vector3D getColorPercentage() const
                {return _colorPercentage;}
            double getSpecular() const {return _specular;}
            double getRoughness() const {return _roughness;}

            Maths::Vector3D getDiffuse() const
                {return _colorPercentage * (1 - _metallic);}
            double getShininess() const {
                if (_roughness)
                    return (2 / std::pow(_roughness, 2)) - 2;
                else
                    return 0;
            }
    
            private:
            std::optional<Ray> getTransmitted(const Ray &ray, const HitInfo &hit) const;
            
            Maths::Vector3D _colorPercentage;
            double _metallic;
            double _specular;
            double _roughness;
            double _opacity;
            double _refraction;
    };

}

#endif
