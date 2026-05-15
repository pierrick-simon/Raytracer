/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#ifndef VERTEXTEXTURE_HPP
    #define VERTEXTEXTURE_HPP
    #include "Vector.hpp"

namespace RayTracer {
    class VertexTexture {
    public:
        double &operator[](size_t index) noexcept;
        const double &operator[](size_t index) const noexcept;

    private:
        Maths::Vector3D _texturePosition;
    };

    std::istream &operator>>(std::istream &stream, VertexTexture &vertex);
} // RayTracer

#endif
