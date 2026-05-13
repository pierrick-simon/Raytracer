/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Raytracer
*/

#ifndef RAYTRACER_HPP
    #define RAYTRACER_HPP

    #include <string>
    #include <optional>
    #include <exception>
    #include <unordered_map>
    #include <thread>
    #include <functional>
    #include <atomic>

    #include "PortablePixMap.hpp"
    #include "DLLoader.hpp"
    #include "IDisplay.hpp"
    #include "ConfigFileParser.hpp"
    #include "Vector.hpp"

namespace RayTracer {
    constexpr int EPISUCCESS = 0;
    constexpr int EPIERROR = 84;
    constexpr int SKIP = -1;
    constexpr std::string_view HELP = "docs/help.txt";
    constexpr std::string_view HELP_FLAG = "--help";
    constexpr std::string_view DISPLAY_FLAG = "--display";
    constexpr std::string_view ARG_EXT = ".cfg";
    constexpr double DOUBLE_OFFSET = 1e-4;

    class RayTracer {
    public:
        RayTracer(std::vector<std::string> args);

        void run() noexcept;
        void throwRays() noexcept;
        
        void rayWorker(Maths::Vector2U start,
            Maths::Vector2U end, Maths::Vector2U res);

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
        int throwDisplay();
        void updateDisplayColor(std::size_t i, std::size_t j, Maths::Color8bit color);
        void parseOptionalArgs(std::vector<std::string> args);
        void initVars(std::reference_wrapper<std::vector<std::string>> args);

        void loadPrimitivePlugins();
        void loadLightPlugins();

        void updateRays(Maths::Vector2U start,
            Maths::Vector2U end, std::vector<Maths::Color> update);

        Maths::Color hitColor(const Ray &ray,
            HitInfo &info, std::size_t depth);
        std::optional<HitInfo> getHitObject(Ray const &ray);
        double getSpecular(const Ray &ray,
            const Ray &lihtRay, HitInfo &info);

        Maths::Color parseObject(const Ray &ray, std::size_t depht);

        Maths::Color parseLight(const Ray &ray, HitInfo &info);

        void updateLoadingBar();

        std::optional<DLLoader<IDisplay>> _displayLoader = std::nullopt;
        std::optional<std::unique_ptr<IDisplay>> _display = std::nullopt;
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
        int _maxDepth = 10;
        int _nbScreenSplit = 4;
        std::mutex _mutex;
        std::vector<std::thread> _workers;
        bool _renderDone = false;

        static BuilderMap
            _presetMaterialBuilders;
        static constexpr std::string_view PLUGINS_FOLDER = "plugins";

    };
};

#endif