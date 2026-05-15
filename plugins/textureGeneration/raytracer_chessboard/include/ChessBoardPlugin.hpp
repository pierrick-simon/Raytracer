/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#ifndef CHESSBOARDPLUGIN_HPP
    #define CHESSBOARDPLUGIN_HPP

    #include "ITextureGenerationPlugin.hpp"

namespace RayTracer {
    class ChessBoardPlugin : public ITextureGenerationPlugin {
    public:
        const std::string_view &getTexturesTypeName() override;

        std::unique_ptr<ITextureGeneration> parseTexture(
            libconfig::Setting const &element) override;

    private:
        static constexpr std::string_view CHESSBOARD_TYPE_NAME = "chessboards";
    };
} // RayTracer

#endif
