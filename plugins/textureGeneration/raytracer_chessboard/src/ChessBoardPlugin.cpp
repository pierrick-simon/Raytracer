/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ChessBoardPlugin
*/

#include <iostream>
#include "ChessBoardPlugin.hpp"
#include "ParserUtils.hpp"
#include "ChessBoard.hpp"

namespace RayTracer {
    const std::string_view &ChessBoardPlugin::getTexturesTypeName()
    {
        return CHESSBOARD_TYPE_NAME;
    }

    std::unique_ptr<ITextureGeneration> ChessBoardPlugin::parseTexture(
        libconfig::Setting const &element)
    {
        std::cout << "Loading chessboard..." << std::endl;
        std::size_t size = ParserUtils::parseSizeT(element, "size");
        std::size_t nbSquare = ParserUtils::parseSizeT(element, "nbSquare");
        Maths::Color color = Maths::Color::BLACK;

        if (element.exists("color"))
            color = ParserUtils::parseColor(element["color"]);
        if (size == 0)
            size = 1;
        if (nbSquare > size)
            nbSquare = size;
        
        return std::make_unique<ChessBoard>(size, nbSquare, color);
    }
}
