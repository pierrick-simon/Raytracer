/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Texture
*/

#include "Texture.hpp"

namespace RayTracer {
    Texture::Texture(std::string fileName) : _ppm(fileName)
    {
    }

    Maths::Color Texture::getColor(Maths::Vector2D uv, bool inf) const
    {
        double u = uv.getX();
        double v = uv.getY();
        if (inf) {
            u = std::fmod(u, _ppm.getWidth());
            v = std::fmod(v, _ppm.getHeight());
            if (u < 0.0)
                u += _ppm.getWidth();
            if (v < 0.0)
                v += _ppm.getHeight();
            v -= _ppm.getHeight();
        } else {
            u *= _ppm.getWidth();
            v *= _ppm.getHeight();
        }
        return _ppm.getPix(u, v);
    }
}
