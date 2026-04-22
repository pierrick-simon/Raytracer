/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#ifndef LIGHTS_HPP
    #define LIGHTS_HPP
#include <vector>
#include "Vector3.hpp"

namespace RayTracer {
    class Lights {
    public:
        Lights(double, double, const std::vector<Maths::Vector3<int>>&, const std::vector<Maths::Vector3<int>>&);

        void setAmbient(double);
        void setDiffuse(double);
        void setPoint(std::vector<Maths::Vector3<int>>);
        void setDirectional(std::vector<Maths::Vector3<int>>);

        [[nodiscard]] double getAmbient() const;
        [[nodiscard]] double getDiffuse() const;
        std::vector<Maths::Vector3<int>> getPoint();
        std::vector<Maths::Vector3<int>> getDirectional();
    private:
        double _ambient = 0.0;
        double _diffuse = 0.0;
        std::vector<Maths::Vector3<int>> _point;
        std::vector<Maths::Vector3<int>> _directional;
    };
}

#endif //LIGHTS_HPP