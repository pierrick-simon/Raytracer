/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#ifndef VERTEXNORMAL_HPP
    #define VERTEXNORMAL_HPP

    #include "Vector.hpp"

namespace RayTracer {
    class VertexNormal {
    public:
        double &operator[](size_t index) noexcept;
    private:
        Maths::Vector3D _vector;
    };

    std::istream &operator>>(std::istream &stream, VertexNormal &vertex);
} // RayTracer

#endif
