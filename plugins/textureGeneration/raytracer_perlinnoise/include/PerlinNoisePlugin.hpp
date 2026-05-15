/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#ifndef PERLINNOISEPLUGIN_HPP
    #define PERLINNOISEPLUGIN_HPP

    #include "ITextureGenerationPlugin.hpp"

namespace RayTracer {
    class PerlinNoisePlugin : public ITextureGenerationPlugin {
    public:
        const std::string_view &getTexturesTypeName() override;

        std::unique_ptr<ITextureGeneration> parseTexture(
            libconfig::Setting const &element) override;

    private:
        static constexpr std::string_view PERLINNOISE_TYPE_NAME = "perlinnoises";
    };
} // RayTracer

#endif
