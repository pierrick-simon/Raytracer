/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** TriangulationData
*/

#ifndef TRIANGULATIONDATA_HPP
    #define TRIANGULATIONDATA_HPP

    #include <array>
    #include <vector>

    #include "Point.hpp"
    #include "Vector.hpp"

namespace RayTracer {
    class TriangulationData {
    public:
        explicit TriangulationData(std::vector<Maths::Point3D> polygon);

        bool triangulate();

        [[nodiscard]] const std::vector<std::array<size_t, 3>> &getTriangles()
            const noexcept;

    private:
        enum class ProjectionAxis {
            X,
            Y,
            Z
        };

        static constexpr double EPSILON = 0.0000001;

        std::vector<Maths::Point3D> _polygon;
        std::vector<size_t> _indices;
        std::vector<std::array<size_t, 3>> _triangles;
        ProjectionAxis _dropAxis = ProjectionAxis::X;
        bool _isCCW = true;

        Maths::Vector3D computeNormal() const;

        static ProjectionAxis pickProjectionAxis(const Maths::Vector3D &normal);
        void projectPoint(const Maths::Point3D &point,
            Maths::Vector2D &projected) const;
        double signedArea2D() const;

        static bool isPointInTriangle2D(const Maths::Vector2D &p,
            const Maths::Vector2D &a, const Maths::Vector2D &b,
            const Maths::Vector2D &c);
        std::array<size_t, 3> makeIndexTriplet(size_t i) const;
        bool isConvexAt(const std::array<size_t, 3> &triplet) const;
        bool containsPointInEar(const std::array<size_t, 3> &triplet) const;
        void appendTriangle(const std::array<size_t, 3> &triplet);
        bool tryClipEar(size_t i);
        bool clipNextEar();
    };
} // RayTracer

#endif

