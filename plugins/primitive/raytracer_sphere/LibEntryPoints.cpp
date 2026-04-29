/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DESCRIPTION
*/

extern "C" RayTracer::IObject *rayTracerLibEntryPoint()
{
    return new RayTracer::PrimitiveSphere();
}

extern "C" RayTracer::LibType rayTracerType()
{
    return RayTracer::LibType::PRIMITIVE;
}

