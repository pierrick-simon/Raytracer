/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#ifndef MODELPLUGIN_HPP
    #define MODELPLUGIN_HPP
    #include "IObjectPlugin.hpp"

namespace RayTracer {
    class ModelPlugin : public IObjectPlugin {
    public:
        const std::string_view &getObjectsTypeName() override;

        std::unique_ptr<IObject> parseObject(
            libconfig::Setting const &, BuilderMap &, TextureGenerationMap &) override;

    private:
        static constexpr std::string_view MODEL_TYPE_NAME = "models";
    };
} // RayTracer

#endif
