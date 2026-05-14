/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** BoundingBox
*/

#ifndef BOUNDINGBOX_HPP
    #define BOUNDINGBOX_HPP

    #include <vector>

    #include "Ray.hpp"
    #include "data/Vertex.hpp"

namespace RayTracer {
    class BoundingBox {
    public:
        BoundingBox();
        BoundingBox(const Maths::Point3D &minPoint,
            const Maths::Point3D &maxPoint);

        static Maths::Vector3D createVertexWithOffset(const Vertex &vertex,
            const Maths::Vector3D &offset);

        static BoundingBox fromVertices(const std::vector<Vertex> &vertices,
            const Maths::Point3D &offset);

        [[nodiscard]] bool hits(const Ray &ray) const;

        bool updateIntersectionInterval(const Ray &ray, size_t axis,
            double &tmin,
            double &tmax) const;

        static bool isIntersectionValid(double tmin, double tmax);

        [[nodiscard]] bool isValid() const;

    private:
        Maths::Point3D _min;
        Maths::Point3D _max;
        bool _valid;
    };
}

#endif

