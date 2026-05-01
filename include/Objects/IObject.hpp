/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ${descriptor}
*/

#ifndef IOBJECT_HPP
    #define IOBJECT_HPP
    #include <optional>
    #include "IMaterial.hpp"
    #include "Info.hpp"

namespace RayTracer {
    class IObject {
    public:
        virtual ~IObject() = default;

        virtual std::optional<HitInfo> hits(Ray &) = 0;
        virtual std::shared_ptr<IMaterial> getIMaterial() = 0;
    };
}

#endif //IOBJECT_HPP