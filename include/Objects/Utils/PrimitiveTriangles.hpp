/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#ifndef PRIMITIVETRIANGLES_HPP
    #define PRIMITIVETRIANGLES_HPP
    #include <IObject.hpp>
    #include <Point3.hpp>
    #include <Ray.hpp>
    #include <Vector3.hpp>

namespace RayTracer {
    class PrimitiveTriangle {
    public:
        PrimitiveTriangle(const Maths::Point3D &a, const Maths::Point3D &b,
            const Maths::Point3D &c, const Maths::RGB &color);

        std::optional<HitInfo> hits(Ray &ray) const;

    private:

        static constexpr double EPSILON = 0.0000001;

        Maths::Point3D _a;
        Maths::Point3D _b;
        Maths::Point3D _c;
        Maths::RGB _color;
    };
}

#endif //PRIMITIVETRIANGLES_HPP