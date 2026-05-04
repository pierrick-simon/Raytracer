/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Material
*/

#include <cstdlib>
#include <algorithm>
#include "RayTracer.hpp"
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

    Material::Builder &Material::Builder::refraction(double refraction)
    {
        _refraction = refraction;
        return *this;
    }

    Material::Material(Builder const &b) :
        _metallic(b.getMetallic()),
        _specular(b.getSpecular()),
        _roughness(b.getRoughness()),
        _opacity(b.getOpacity()),
        _refraction(b.getRefraction())
    {
        _colorPercentage.x = 
            (double)b.getColor().x / std::numeric_limits<unsigned char>::max();
        _colorPercentage.y = 
            (double)b.getColor().y / std::numeric_limits<unsigned char>::max();
        _colorPercentage.z = 
            (double)b.getColor().z / std::numeric_limits<unsigned char>::max();
        _metallic = std::clamp(_metallic, 0.0, 1.0);
        _specular = std::clamp(_specular, 0.0, 1.0);
        _roughness = std::clamp(_roughness, 0.0, 1.0);
        _opacity = std::clamp(_opacity, 0.0, 1.0);
    }

    Ray Material::reflect(const Ray &ray, const HitInfo &hit) const
    {
        Ray reflected = ray;

        reflected.strength *= _metallic + (1.0 - _metallic) * _specular;
        if (reflected.strength >= DOUBLE_OFFSET) {
            Maths::Vector3D perfectReflect = ray.direction
                - hit.impactNormal * 2.0 * ray.direction.dot(hit.impactNormal);
            reflected.direction = perfectReflect * (1.0 - _roughness);
            reflected.direction = reflected.direction.normalized();
            reflected.colorPercentage *= _colorPercentage * _metallic
                + Maths::Vector3D(1, 1, 1) * (1.0 - _metallic) * _specular;
            reflected.origin = hit.hitPos + hit.impactNormal * DOUBLE_OFFSET;
        }
        return reflected;
    }

    std::optional<Ray> Material::getTransmitted(
        const Ray &ray, const HitInfo &hit) const
    {
        std::optional<Ray> transmitted = ray;
        double refraction = 1.0 / _refraction;
        Maths::Vector3D normal = hit.impactNormal;
        if (ray.direction.dot(hit.impactNormal) < 0) {
            refraction = _refraction;
            normal = hit.impactNormal * -1;
        }
        double cosI  = ray.direction.dot(normal) * -1;
        double sin2T = refraction * refraction * (1.0 - cosI * cosI);
        if (sin2T > 1.0)
            transmitted = std::nullopt;
        else {
            double cosT = std::sqrt(1.0 - sin2T);
            transmitted->direction = ray.direction * refraction
                                + normal * (refraction * cosI - cosT);
            transmitted->direction = transmitted->direction.normalized();
            transmitted->colorPercentage *= _colorPercentage * (1.0 - _opacity);
            transmitted->strength *= (1.0 - _opacity);
            transmitted->origin = hit.hitPos + hit.impactNormal * DOUBLE_OFFSET;
        }
        return transmitted;
    }

    std::optional<Ray> Material::through(const Ray &ray, const HitInfo &hit) const
    {
        std::optional<Ray> transmitted = ray;
        transmitted->strength *= (1.0 - _opacity);
        if (!(_opacity >= 1.0 || _refraction == 0
            || transmitted->strength < DOUBLE_OFFSET))
            transmitted = std::nullopt;
        else 
            transmitted = getTransmitted(ray, hit);
        return transmitted;
    }

    Ray Material::diffuse(const Ray &ray, const HitInfo &hit) const
    {
        Ray diffused = ray;

        diffused.strength *= (1.0 - _metallic) * (1.0 - _specular) * _roughness;
        if (diffused.strength >= DOUBLE_OFFSET) {
            diffused.direction = hit.impactNormal.normalized();
            diffused.colorPercentage = _colorPercentage;
            diffused.origin = hit.hitPos + hit.impactNormal * DOUBLE_OFFSET;
        }
        return diffused;
    }
    
}
