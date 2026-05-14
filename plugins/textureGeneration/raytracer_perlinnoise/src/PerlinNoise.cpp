/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PerlinNoise
*/

#include <iostream>
#include "PerlinNoise.hpp"

namespace RayTracer {
    PerlinNoise::PerlinNoise(Maths::Vector2U size, std::size_t seed)
        : _size(size), _seed(seed)
    {
    }


    PortablePixMap PerlinNoise::generate()
    {
        PortablePixMap map(_size.getX(), _size.getY());
        return map;
    }
}
