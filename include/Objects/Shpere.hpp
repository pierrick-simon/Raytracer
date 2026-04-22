/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#ifndef SHPERE_HPP
    #define SHPERE_HPP
    #include "Vector3.hpp"
    #include "IObject.hpp"

namespace RayTracer {
    class Sphere : public IObject {
    public:
        Sphere(int, int, int, Maths::RGB);

        void setX(int);
        void setY(int);
        void setZ(int);
        void setColor(Maths::RGB);

        [[nodiscard]] int getX() const;
        [[nodiscard]] int getY() const;
        [[nodiscard]] int getZ() const;
        [[nodiscard]] Maths::RGB getColor() const;
    private:
        int _x = 0;
        int _y = 0;
        int _z = 0;
        Maths::RGB _color;
    };
}

#endif //SHPERE_HPP