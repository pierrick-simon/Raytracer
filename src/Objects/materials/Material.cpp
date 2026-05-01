/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Material
*/

#include "Material.hpp"

namespace RayTracer {

    Material::Material(Maths::RGB color, double metallic, double specular,
        double roughness, double opacity) :
        _metallic(metallic),
        _specular(specular),
        _roughness(roughness),
        _opacity(opacity)
    {
        _colorPercentage.x =
            (double)color.x / std::numeric_limits<unsigned char>::max();
        _colorPercentage.x =
            (double)color.x / std::numeric_limits<unsigned char>::max();
        _colorPercentage.x =
            (double)color.x / std::numeric_limits<unsigned char>::max();
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
