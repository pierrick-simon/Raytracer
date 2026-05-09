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
    class Color : public Vector<4, double> {
    public:
        Color() = default;

        Color(double r, double g, double b, double a = 1.0);

        explicit Color(const Vector3D &color, double a = 1.0);

        static Color from8Bit(unsigned char r, unsigned char g, unsigned char b,
            unsigned char a =  std::numeric_limits<unsigned char>::max());

        [[nodiscard]] Vector<4, unsigned char> to8Bit() const;

        [[nodiscard]] double &getR();

        [[nodiscard]] const double &getR() const;

        [[nodiscard]] double &getG();

        [[nodiscard]] const double &getG() const;

        [[nodiscard]] double &getB();

        [[nodiscard]] const double &getB() const;

        [[nodiscard]] double &getA();

        [[nodiscard]] const double &getA() const;
    };
} // Maths

#endif
