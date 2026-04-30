/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DESCRIPTION
*/

#include "IObjectPlugin.hpp"
#include "RayTracer.hpp"
#include "SpherePlugin.hpp"

extern "C" RayTracer::IObjectPlugin *rayTracerLibEntryPoint()
{
    return new RayTracer::SpherePlugin();
}

extern "C" RayTracer::LibType rayTracerType()
{
    return RayTracer::LibType::PRIMITIVE;
}

