/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Material
*/

#ifndef MATERIAL_HPP
    #define MATERIAL_HPP

    #include <optional>
    #include "Vector3.hpp"
    #include "Info.hpp"

namespace RayTracer
{
    class Material {
        public:
            Material(Maths::RGB color, double metallic, double specular,
                double roughness, double opacity);

            void scatter(Ray &, HitInfo &);

        private:
            void handleColor(Ray &);
                
            Maths::Vector3D _colorPercentage;
            double _metallic;
            double _specular;
            double _roughness;
            double _opacity;
    };

}

#endif
