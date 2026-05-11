/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#include "IObjectPlugin.hpp"
#include "RayTracer.hpp"
#include "ConePlugin.hpp"

extern "C" RayTracer::IObjectPlugin *rayTracerLibEntryPoint()
{
    return new RayTracer::ConePlugin();
}

extern "C" RayTracer::LibType rayTracerType()
{
    return RayTracer::LibType::PRIMITIVE;
}
