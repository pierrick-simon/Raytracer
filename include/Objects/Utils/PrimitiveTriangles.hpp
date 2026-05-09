/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#ifndef PRIMITIVETRIANGLES_HPP
    #define PRIMITIVETRIANGLES_HPP
    #include <IObject.hpp>
    #include <Point.hpp>
    #include <Ray.hpp>
    #include <Vector.hpp>

namespace RayTracer {
    class PrimitiveTriangle {
    public:
        PrimitiveTriangle(const Maths::Point3D &a, const Maths::Point3D &b,
            const Maths::Point3D &c, const Material &mat);

        std::optional<HitInfo> fillHitInfo(Ray const &ray, Maths::Vector3D const &AB,
            Maths::Vector3D const &AC, double t);

        std::optional<HitInfo> rayTriangleMollerTrumboreAlgo(Ray const &ray,
            Maths::Vector3D AB, Maths::Vector3D AC, Maths::Vector3D h);

        std::optional<HitInfo> hits(Ray const &ray);

    private:

        static constexpr double EPSILON = 0.0000001;

        Maths::Point3D _a;
        Maths::Point3D _b;
        Maths::Point3D _c;
        Material _material;
    };
}

#endif //PRIMITIVETRIANGLES_HPP