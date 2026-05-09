/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#ifndef COLOR_HPP
    #define COLOR_HPP
    #include "Vector.hpp"

namespace Maths {

class Color : Vector<4, double> {
public:
    static Color fromRGB(unsigned char);
};

} // Maths

#endif
