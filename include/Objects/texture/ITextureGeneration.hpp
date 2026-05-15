/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ITextureGeneration
*/

#ifndef ITEXTUREGENERATION_HPP
    #define ITEXTUREGENERATION_HPP

    #include "PortablePixMap.hpp"

namespace RayTracer {
    class ITextureGeneration {
        public:
            virtual ~ITextureGeneration() = default;

            virtual PortablePixMap generate() = 0;
    };
}

#endif
