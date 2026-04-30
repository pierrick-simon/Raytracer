/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DisplaySFML
*/

#include "LibType.hpp"
#include "../include/PrimitiveSphere.hpp"

std::optional<RayTracer::HitInfo> RayTracer::PrimitiveSphere::hits(RayTracer::Ray &ray)
{
    ray.origin.x -= _origin.x;
    ray.origin.y -= _origin.y;
    ray.origin.z -= _origin.z;

    double a = (ray.direction.x * ray.direction.x) + (ray.direction.y * ray.direction.y) + (ray.direction.z * ray.direction.z);
    double b = ray.direction.dot(Maths::Vector3D(ray.origin)) * 2;
    double c = (ray.origin.x * ray.origin.x) + (ray.origin.y * ray.origin.y) + (ray.origin.z * ray.origin.z) - (_radius * _radius);
    double delta = (b * b) - (4 * a * c);
    if (delta >= 0)
        return {};
    return {};
}

extern "C" RayTracer::IObject *rayTracerLibEntryPoint()
{
    return new RayTracer::PrimitiveSphere();
}

extern "C" RayTracer::LibType rayTracerType()
{
    return RayTracer::LibType::PRIMITIVE;
}
