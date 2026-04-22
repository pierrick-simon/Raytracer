/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#ifndef SHPERE_HPP
    #define SHPERE_HPP
    #include "Vector3.hpp"

namespace RayTracer {
    class Sphere {
    public:
        Sphere(int, int, int, Maths::Vector3<int>);

        void setX(int);
        void setY(int);
        void setZ(int);
        void setColor(Maths::Vector3<int>);

        [[nodiscard]] int getX() const;
        [[nodiscard]] int getY() const;
        [[nodiscard]] int getZ() const;
        [[nodiscard]] Maths::Vector3<int> getColor() const;
    private:
        int _x = 0;
        int _y = 0;
        int _z = 0;
        Maths::Vector3<int> _color;
    };
}

#endif //SHPERE_HPP