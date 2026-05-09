/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Material
*/

#ifndef MATERIAL_HPP
    #define MATERIAL_HPP

    #include <optional>
    #include "Vector.hpp"
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


            Ray getReflectRay(const Ray &ray, const HitInfo &hit) const;
            std::optional<Ray> getRefractRay(const Ray &ray, const HitInfo &hit) const;
            double getFresnel(const Ray &ray, const HitInfo &hit) const;

            Maths::Vector3D getColorPercentage() const
                {return _colorPercentage;}
            double getSpecular() const {return _specular;}
            double getRoughness() const {return _roughness;}
            double getOpacity() const {return _opacity;}

            Maths::Vector3D getDiffuse() const
                {return _colorPercentage * (1 - _metallic);}
            double getShininess() const
                {return (1 - _roughness) * 100;}
    
        private:            
            Maths::Vector3D _colorPercentage;
            double _metallic;
            double _specular;
            double _roughness;
            double _opacity;
            double _refraction;
    };

}

#endif
