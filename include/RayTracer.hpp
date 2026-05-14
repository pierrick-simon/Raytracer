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
    #include <chrono>

    #include "PortablePixMap.hpp"
    #include "DLLoader.hpp"
    #include "IDisplay.hpp"
    #include "ConfigFileParser.hpp"
    #include "Vector.hpp"

namespace RayTracer {
    constexpr int EPISUCCESS = 0;
    constexpr int EPIERROR = 84;
    constexpr int SKIP = -1;
    constexpr int EXIT = 1;
    constexpr std::string_view HELP = "docs/help.txt";
    constexpr std::string_view HELP_FLAG = "--help";
    constexpr std::string_view DISPLAY_FLAG = "--display";
    constexpr std::string_view ARG_EXT = ".cfg";
    constexpr double DOUBLE_OFFSET = 1e-4;
    constexpr int LOW_QUALITY_SCALE = 10;
    constexpr int LOW_QUALITY_DEPTH = 3;
    constexpr auto SLEEP = std::chrono::milliseconds(300);
    
    using Clock = std::chrono::steady_clock;
    
    class RayTracer {
    public:
        RayTracer(std::vector<std::string> args);

        void run() noexcept;

        void throwRays(std::size_t scale, std::size_t maxDepth) noexcept;

        void rayWorker(Maths::Vector2U start, Maths::Vector2U end,
            Maths::Vector2U res, std::size_t scale, std::size_t maxDepth);

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
        void cancelAndJoin(std::thread &thread);
        std::thread startRender(std::size_t scale, std::size_t maxDepth);
        void updateRays(Maths::Vector2U start,
            Maths::Vector2U end, std::vector<Maths::Color> update);
        void rayWorkerBatch(std::size_t scale, std::size_t x, std::size_t y,
            std::vector<Maths::Color> &update, Maths::Color color);

        void throwDisplay();

        void updateDisplayColor(std::size_t i, std::size_t j,
            Maths::Color8bit color);
        bool moveCamera(Action action);
        bool rotateCamera(Action action);
        int handleEvent(Event event, Clock::time_point &clock, bool &sleep,
            bool &lowQuality, std::thread &thread);
        void updateCamera(Clock::time_point &clock, bool &sleep,
            bool &lowQuality, std::thread &thread);

        void parseOptionalArgs(std::vector<std::string> args);
        void initVars(std::reference_wrapper<std::vector<std::string>> args);

        void loadPrimitivePlugins();
        void loadLightPlugins();

        Maths::Color hitColor(const Ray &ray, HitInfo &info,
            std::size_t depth, int maxDepth);
        std::optional<HitInfo> getHitObject(Ray const &ray);
        double getSpecular(const Ray &ray,
            const Ray &lightRay, HitInfo &info);
        Maths::Color parseObject(const Ray &ray,
            std::size_t depth, int maxDepth);
        Maths::Color parseLight(const Ray &ray, HitInfo &info);

        void updateLoadingBar();

        void makeWorker(Maths::Vector2U resolution, std::size_t scale,
            std::size_t maxDepth, double stepX, double stepY);

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

        std::atomic<bool> _renderDone  = false;
        std::atomic<bool> _cancelRender = false;

        static BuilderMap _presetMaterialBuilders;
        static constexpr std::string_view PLUGINS_FOLDER = "plugins";
    };
};

#endif