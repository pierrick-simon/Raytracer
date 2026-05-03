/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#include "IObjectPlugin.hpp"
#include "RayTracer.hpp"
#include "PyramidPlugin.hpp"

extern "C" RayTracer::IObjectPlugin *rayTracerLibEntryPoint()
{
    return new RayTracer::PyramidPlugin();
}

extern "C" RayTracer::LibType rayTracerType()
{
    return RayTracer::LibType::PRIMITIVE;
}
