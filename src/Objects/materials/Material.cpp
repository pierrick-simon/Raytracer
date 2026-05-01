/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Material
*/

#include "Material.hpp"

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
        _metallic(b._metallic),
        _specular(b._specular),
        _roughness(b._roughness),
        _opacity(b._opacity)
    {
        _colorPercentage.x = 
            (double)b._color.x / std::numeric_limits<unsigned char>::max();
        _colorPercentage.y = 
            (double)b._color.y / std::numeric_limits<unsigned char>::max();
        _colorPercentage.z = 
            (double)b._color.z / std::numeric_limits<unsigned char>::max();
    }

    void Material::scatter(Ray &ray, HitInfo &info)
    {
        ray.colorPercentage *= _colorPercentage * ray.strenght;
        ray.strenght *= _metallic;
        ray.origin = info.hitPos;
        if (ray.strenght)
            ray.direction = ray.direction - (info.impactNormal * 2 * 
                (ray.direction.dot(info.impactNormal)));
    }
}
