/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#include "ITextureGenerationPlugin.hpp"
#include "RayTracer.hpp"
#include "PerlinNoisePlugin.hpp"

extern "C" RayTracer::ITextureGenerationPlugin *rayTracerLibEntryPoint()
{
    return new RayTracer::PerlinNoisePlugin();
}

extern "C" RayTracer::LibType rayTracerType()
{
    return RayTracer::LibType::TEXTURE_GENERATION;
}
