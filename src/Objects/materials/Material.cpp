/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Material
*/

#include "Material.hpp"
#include "Info.hpp"

namespace RayTracer {

    Material::Builder &Material::Builder::color(Maths::RGB color)
    {
        _color = color;
        return *this;
    }

    Material::Builder &Material::Builder::metallic(double metallic)
    {
        _metallic = metallic;
        return *this;
    }

    Material::Builder &Material::Builder::specular(double specular)
    {
        _specular = specular;
        return *this;
    }

    Material::Builder &Material::Builder::roughness(double roughness)
    {
        _roughness = roughness;
        return *this;
    }

    Material::Builder &Material::Builder::opacity(double opacity)
    {
        _opacity = opacity;
        return *this;
    }

    Material::Material(Builder const &b) :
        _metallic(b.getMetallic()),
        _specular(b.getSpecular()),
        _roughness(b.getRoughness()),
        _opacity(b.getOpacity())
    {
        _colorPercentage.x = 
            (double)b.getColor().x / std::numeric_limits<unsigned char>::max();
        _colorPercentage.y = 
            (double)b.getColor().y / std::numeric_limits<unsigned char>::max();
        _colorPercentage.z = 
            (double)b.getColor().z / std::numeric_limits<unsigned char>::max();
    }

    void Material::scatter(Ray &ray, HitInfo &info)
    {
        ray.colorPercentage = _colorPercentage;
    }
}
