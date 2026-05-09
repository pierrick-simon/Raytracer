/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#include "Color.hpp"

#include <algorithm>
#include <cmath>

namespace Maths {
    Color::Color(double r, double g, double b, double a) :
        Vector(r, g, b, a)
    {
    }

    Color::Color(const Vector3D &color, double a) :
        Vector(color.getX(), color.getY(), color.getZ(), a)
    {
    }

    Color Color::from8Bit(unsigned char r, unsigned char g, unsigned char b,
        unsigned char a)
    {
        return {
            r / 255.0,
            g / 255.0,
            b / 255.0,
            a / 255.0
        };
    }

    static unsigned char doubleToByte(double val)
    {
        val = std::clamp(val, 0.0, 1.0);
        return static_cast<unsigned char>(std::lround(val * 255.0));
    }

    Vector<4, unsigned char> Color::to8Bit() const
    {
        return Vector<4, unsigned char>(doubleToByte(getR()),
            doubleToByte(getG()),
            doubleToByte(getB()), doubleToByte(getA()));
    }

    double &Color::getR()
    {
        return getX();
    }

    const double &Color::getR() const
    {
        return getX();
    }

    double &Color::getG()
    {
        return getY();
    }

    const double &Color::getG() const
    {
        return getY();
    }

    double &Color::getB()
    {
        return getZ();
    }

    const double &Color::getB() const
    {
        return getZ();
    }

    double &Color::getA()
    {
        return getW();
    }

    const double &Color::getA() const
    {
        return getW();
    }
} // Maths
