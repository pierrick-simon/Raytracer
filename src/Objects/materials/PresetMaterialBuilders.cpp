/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** PresetMaterials
*/

#include "ConfigFileParser.hpp"

namespace RayTracer {

    BuilderMap
        ConfigFileParser::_presetMaterialBuilders = {
        {
            "Flat color",
            Material::Builder()
                .metallic(0)
                .roughness(1)
                .specular(0.04)
                .opacity(1)
                .refraction(1)
        },
        {
            "Mirror",
            Material::Builder()
                .metallic(1)
                .roughness(0)
                .specular(1)
                .opacity(1)
                .refraction(1)
        },
        {
            "Brushed metal",
            Material::Builder()
                .metallic(1)
                .roughness(0.3)
                .specular(1)
                .opacity(1)
                .refraction(1)
        },
        {
            "Plastic",
            Material::Builder()
                .metallic(0)
                .roughness(0.2)
                .specular(0.05)
                .opacity(1)
                .refraction(1.5)
        },
        {
            "Glass",
            Material::Builder()
                .metallic(0)
                .roughness(0)
                .specular(0.04)
                .opacity(0)
                .refraction(1.52)
        },
        {
            "Water",
            Material::Builder()
                .metallic(0)
                .roughness(0)
                .specular(0.03)
                .opacity(0.02)
                .refraction(1.33)
        },
        {
            "Diamond",
            Material::Builder()
                .metallic(0)
                .roughness(0)
                .specular(0.04)
                .opacity(0)
                .refraction(2.42)
        },
        {
            "Ice",
            Material::Builder()
                .metallic(0)
                .roughness(0.1)
                .specular(0.04)
                .opacity(0.1)
                .refraction(1.31)
        },
        {
            "Wood",
            Material::Builder()
                .metallic(0)
                .roughness(0.9)
                .specular(0.04)
                .opacity(1)
                .refraction(1)
        }
    };
};