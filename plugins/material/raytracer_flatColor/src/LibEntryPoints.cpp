/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DESCRIPTION
*/

#include "IMaterialPlugin.hpp"
#include "RayTracer.hpp"
#include "FlatColorPlugin.hpp"

extern "C" RayTracer::IMaterialPlugin *rayTracerLibEntryPoint()
{
    return new RayTracer::FlatColorPlugin();
}

extern "C" RayTracer::LibType rayTracerType()
{
    return RayTracer::LibType::MATERIAL;
}
