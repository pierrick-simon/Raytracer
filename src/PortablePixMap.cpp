/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PortablePixMap
*/

#include <filesystem>
#include <fstream>
#include <iomanip>
#include "PortablePixMap.hpp"

RayTracer::PortablePixMap::PortablePixMap(std::string filepath)
{
    std::ifstream file(filepath);

    if (!filepath.ends_with(EXT) || filepath.size() <= EXT.size() + 1)
        throw WrongExtensionException();
    if (!file.is_open())
        throw NoSuchFileException();
    std::string line;
    if (!readType(file) || !readSize(file) || !readMaxSize(file))
        throw FileException();
    while (customGetline(line, file))
        if (!readBody(line))
            throw FileException();
    if (_map.size() != _height * _width) {
        throw FileException();
    }
}

void RayTracer::PortablePixMap::setPix(
    std::size_t width, std::size_t height, Maths::Color pix)
{
    if (_height <= height || _width <= width)
        throw  OutOfRangeException();
    size_t idx = height * _width + width;
    _map[idx] = pix;
}

Maths::Color RayTracer::PortablePixMap::getPix(
    std::size_t width, std::size_t height)
{
    if (_height <= height || _width <= width)
        throw  OutOfRangeException();
    size_t idx = height * _width + width;
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
    for (auto &pix: _map) {
        auto rgbColor = pix.to8Bit();
        file << +rgbColor.getX() << " ";
        file << +rgbColor.getY() << " ";
        file << +rgbColor.getZ() << "\n";
    }
}

bool RayTracer::PortablePixMap::customGetline(
    std::reference_wrapper<std::string> str,
    std::reference_wrapper<std::ifstream> file)
{
    bool value = false;
    if (std::getline(file.get(), str.get())) {
        value = true;
        size_t pos = str.get().find("#");
        if (pos != std::string::npos)
            str.get().replace(pos, str.get().length() - pos, "\0");
        if (str.get().empty())
            value = customGetline(str, file);
    }
    return value;
}

bool RayTracer::PortablePixMap::readType(
    std::reference_wrapper<std::ifstream> file)
{
    bool value = true;
    std::string line;
    if (!customGetline(line, file))
        value = false;
    else {
        std::istringstream stream(line);
        std::string tmp;
        stream >> tmp;
        if (stream.fail() || !stream.eof() || tmp != PPM_TYPE)
            value = false;
    }
    return value;
}

bool RayTracer::PortablePixMap::readSize(
    std::reference_wrapper<std::ifstream> file)
{
    bool value = true;
    std::string line;
    if (!customGetline(line, file))
        value = false;
    else {
        std::istringstream stream(line);
        int width;
        int height;
        stream >> width >> height;
        if (stream.fail() || !stream.eof() || width <= 0 || height <= 0)
            value = false;
        _height = height;
        _width = width;
    }
    return value;
}

bool RayTracer::PortablePixMap::readMaxSize(
    std::reference_wrapper<std::ifstream> file)
{
    bool value = true;
    std::string line;
    if (!customGetline(line, file))
        value = false;
    else {
        std::istringstream stream(line);
        int tmp;
        stream >> tmp;
        if (stream.fail() || !stream.eof() || tmp != static_cast<int>(
            std::numeric_limits<unsigned char>::max()))
            value = false;
    }
    return value;
}

bool RayTracer::PortablePixMap::readBody(std::string line)
{
    bool value = true;
    std::istringstream tmp(line);
    int r;
    int g;
    int b;
    tmp >> r >> g >> b;
    int maxChar = std::numeric_limits<unsigned char>::max();
    if (tmp.fail() || !tmp.eof()
        || r < 0 || r > maxChar
        || g < 0 || g > maxChar
        || b < 0 || b > maxChar)
        value = false;
    else
        _map.push_back(Maths::Color::from8Bit(r, g, b));
    return value;
}
