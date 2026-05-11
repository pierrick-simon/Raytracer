/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Material
*/

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "RayTracer.hpp"
#include "Material.hpp"
#include "Info.hpp"

namespace RayTracer {

    Material::Builder &Material::Builder::color(Maths::Color color)
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
        _refraction(b.getRefraction()),
        _color(b.getColor())
    {
        _metallic = std::clamp(_metallic, 0.0, 1.0);
        _specular = std::clamp(_specular, 0.0, 1.0);
        _roughness = std::clamp(_roughness, 0.0, 1.0);
        _opacity = std::clamp(_opacity, 0.0, 1.0);
        _color.clamp();
    }

    Ray Material::getReflectRay(const Ray &ray, const HitInfo &hit) const
    {
        Maths::Vector3D reflect = ray.direction
                - hit.impactNormal * 2.0 * ray.direction.dot(hit.impactNormal);
        Maths::Vector3D delta = hit.impactNormal * DOUBLE_OFFSET;
        return {hit.hitPos + delta,
            reflect.normalized()};
    }

    static Maths::Vector3D refract(const Maths::Vector3D &uv, const Maths::Vector3D &n, double eta)
    {
        auto cos_theta = std::min(-uv.dot(n), 1.0);
        Maths::Vector3D r_out_perp = (uv + n * cos_theta) * eta;
        Maths::Vector3D r_out_par = n * -std::sqrt(std::abs(1.0 - r_out_perp.norm_squared()));
        return r_out_perp + r_out_par;
    }

    std::optional<Ray> Material::scatter(const Ray &ray, const HitInfo &hit) const
    {
        double ri = hit.impactNormal.dot(ray.direction) >= 0 ? 1.0 / this->_refraction : this->_refraction;

        Maths::Vector3D unit_dir = ray.direction.normalized();
        Maths::Vector3D refracted = refract(unit_dir, hit.impactNormal, ri);

        return Ray{hit.hitPos, refracted};
    }

    std::optional<Ray> Material::getRefractRay(
        const Ray &ray, const HitInfo &hit) const
    {
        return scatter(ray, hit);
        // std::optional<Ray> refract = std::nullopt;
        // Maths::Vector3D N = hit.impactNormal;
        // double cosI = ray.direction.dot(N);
        // double n1 = 1.0;
        // double n2 = _refraction;
        //
        // if (cosI > DOUBLE_OFFSET) {
        //     std::swap(n1, n2);
        //     N *= -1;
        // }
        // cosI = std::abs(cosI);
        // double eta = n2 ? n1 / n2 : 0;
        // double k = 1.0 - eta * eta * (1.0 - cosI * cosI);
        // if (k >= DOUBLE_OFFSET) {
        //     Maths::Vector3D T = ray.direction * eta - N * (eta * cosI + std::sqrt(k));
        //     Maths::Vector3D delta = N * DOUBLE_OFFSET;
        //     refract = {hit.hitPos - delta, T.normalized()};
        // } else {
        //     HitInfo info = hit;
        //     info.impactNormal = N;
        //     refract = getReflectRay(ray, info);
        // }
        // return refract;
    }

    double Material::getFresnel(const Ray &ray, const HitInfo &hit) const
    {
        Maths::Vector3D N = hit.impactNormal;
        Maths::Vector3D V = ray.direction.normalized() * -1;

        double cosT = std::max(0.0, N.dot(V));

        double n1 = 1.0;
        double n2 = _refraction;

        double F0 = std::pow((n1 - n2) / (n1 + n2), 2);
        F0 = F0 * (1 - _metallic) + _metallic;

        return F0 + (1 - F0) * std::pow(1 - cosT, 5);
    }
}
