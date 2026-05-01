/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** MaterialFlatColor
*/

#include "MaterialFlatColor.hpp"

namespace RayTracer
{
    std::optional<ScatterInfo> MaterialFlatColor::scatter(
        Ray &ray, HitInfo &info)
    {
        return ScatterInfo{{info.hitPos, info.impactNormal}, _color};
    }
}
