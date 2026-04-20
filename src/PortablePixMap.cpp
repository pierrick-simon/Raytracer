/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PortablePixMap
*/

#include <filesystem>
#include <fstream>
#include "PortablePixMap.hpp"

void RayTracer::PortablePixMap::setPix(
    std::size_t width, std::size_t height, Maths::RGB pix)
{
    if (_height <= height || _width <= width)
        throw  OutOfRangeException();
    size_t idx = height * width;
    _map[idx] = pix;
}

Maths::RGB RayTracer::PortablePixMap::getPix(
    std::size_t width, std::size_t height)
{
    if (_height <= height || _width <= width)
        throw  OutOfRangeException();
    size_t idx = height * width;
    return _map[idx];
}

void RayTracer::PortablePixMap::save(std::string name)
{
    std::filesystem::path dir(SCREEN);
    if (!std::filesystem::exists(dir))
        std::filesystem::create_directories(dir);
    std::ofstream file(
        std::string(SCREEN) + "/" + name + std::string(EXT));
    if (!file.is_open())
        return;
    file << PPM_TYPE << "\n";
    file << _width << " " << _height << "\n";
    file << +std::numeric_limits<unsigned char>::max()
        << "\n";
    for (Maths::RGB pix: _map) {
        file << +pix.x << " ";
        file << +pix.y << " ";
        file << +pix.z << "\n";
    }
}
