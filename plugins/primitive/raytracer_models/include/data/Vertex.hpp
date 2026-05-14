/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#ifndef VERTEX_HPP
    #define VERTEX_HPP
    #include <iosfwd>

    #include "Vector.hpp"

namespace RayTracer {
    using Vertex = Maths::Vector<4, double>;

    std::istream &operator>>(std::istream &stream, Vertex &vertex);
} // RayTracer

#endif
