/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** IMaterial
*/

#ifndef IMATERIAL_HPP
    #define IMATERIAL_HPP

#include "Info.hpp"

namespace RayTracer {

    class IMaterial {
        public:
            ~IMaterial() = default;

            virtual std::optional<ScatterInfo> scatter(Ray &, HitInfo &) = 0;
    };
}

#endif
