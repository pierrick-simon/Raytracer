/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Raytracer
*/

#ifndef RAYTRACER_HPP
    #define RAYTRACER_HPP

    #include <queue>
    #include <string>
    #include <optional>
    #include <exception>
    #include <unordered_map>

    #include "PortablePixMap.hpp"
    #include "DLLoader.hpp"
    #include "IDisplay.hpp"
    #include "ConfigFileParser.hpp"

namespace RayTracer {
    constexpr int EPISUCCESS = 0;
    constexpr int EPIERROR = 84;
    constexpr std::string_view HELP = "docs/help.txt";
    constexpr std::string_view HELP_FLAG = "--help";
    constexpr std::string_view DISPLAY_FLAG = "--display";
    constexpr std::string_view ARG_EXT = ".cfg";
    constexpr double DOUBLE_OFFSET = 1e-4;
    constexpr std::size_t MAX_DEPTH = 10;

    class RayTracer {
    public:
        RayTracer(std::queue<std::string> args);

        void run() noexcept;
        void throwRays() noexcept;
        void setPixel(
            std::size_t x, std::size_t y, Maths::Vector2U resolution) noexcept;

        static void showHelp();

        class HelpException : public std::exception {
        public:
            const char *what() const noexcept override
            { return "Show Help."; }
        };

        class IncorrectLibTypeException : public std::exception {
        public:
            const char *what() const noexcept override;
        };

    private:
        void runDisplay();
        void parseOptionalArgs(std::queue<std::string> args);
        void initVars(std::reference_wrapper<std::queue<std::string>> args);

        void loadPrimitivePlugins();
        void loadLightPlugins();

        Maths::Color hitColor(const Ray &ray,
            HitInfo &info, std::size_t depth);
        std::optional<HitInfo> getHitObject(Ray const &ray);
        double getSpecular(const Ray &ray,
            const Ray &lihtRay, HitInfo &info);

        Maths::Color parseObject(const Ray &ray, std::size_t depht);

        Maths::Color parseLight(const Ray &ray, HitInfo &info);

        void loadingBar(std::size_t pix);

        std::optional<DLLoader<IDisplay>> _display = std::nullopt;
        PortablePixMap _ppm;
        std::string _name;
        Camera _camera;
        std::vector<DLLoader<IObjectPlugin>> _primitivesPluginsLoaders;
        std::vector<std::unique_ptr<IObjectPlugin>> _primitivesPlugins;
        std::vector<std::unique_ptr<IObject>> _objects;
        std::vector<DLLoader<ILightSourcePlugin>> _lightsPluginsLoaders;
        std::vector<std::unique_ptr<ILightSourcePlugin>> _lightsPlugins;
        LightConfig _lights;
        double _loadingPercentage = 0.0;

        static BuilderMap
            _presetMaterialBuilders;
        static constexpr std::string_view PLUGINS_FOLDER = "plugins";
    };
};

#endif