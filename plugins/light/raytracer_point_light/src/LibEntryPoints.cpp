/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DESCRIPTION
*/

#include "ILightSourcePlugin.hpp"
#include "RayTracer.hpp"
#include "PointLightPlugin.hpp"

extern "C" {

RayTracer::ILightSourcePlugin *rayTracerLibEntryPoint()
{
    return new RayTracer::PointLightPlugin();
}

RayTracer::LibType rayTracerType()
{
    return RayTracer::LibType::LIGHT_SOURCE;
}

} // extern "C"
