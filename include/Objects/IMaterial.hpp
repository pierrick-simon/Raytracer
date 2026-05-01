/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** IMaterial
*/

#ifndef IMATERIAL_HPP
    #define IMATERIAL_HPP

#include "Ray.hpp"
#include "Vector3.hpp"
#include "IObject.hpp"


namespace RayTracer {

    struct ScatterInfo {
        Ray scattered;
        Maths::RGB color;
    };

    class IMaterial {
        public:
            ~IMaterial() = default;

            virtual std::optional<ScatterInfo> scatter(Ray &, HitInfo &) = 0;
    };
}

#endif
