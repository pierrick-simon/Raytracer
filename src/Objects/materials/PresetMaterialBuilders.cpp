/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PresetMaterials
*/

#include "RayTracer.hpp"

namespace RayTracer {

    BuilderMap
        RayTracer::_presetMaterialBuilders = {
        {
            "flat color",
            Material::Builder()
                .metallic(0)
                .roughness(0)
                .specular(0.5)
                .opacity(1)
        },
    };

};