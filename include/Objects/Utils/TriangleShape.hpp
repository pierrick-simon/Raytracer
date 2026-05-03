/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#ifndef TRIANGLESHAPE_HPP
    #define TRIANGLESHAPE_HPP
    #include <IObject.hpp>
	#include <PrimitiveTriangles.hpp>
    #include <vector>

namespace RayTracer {
    class TriangleShape {
    public:
        TriangleShape() = default;

        TriangleShape(std::initializer_list<PrimitiveTriangle> triangles)
            : _triangles(triangles) {}

        template<typename T>
        TriangleShape(const T &triangles)
            : _triangles(triangles.begin(), triangles.end()) {}

        std::optional<HitInfo> hits(Ray &ray);

    private:
        std::vector<PrimitiveTriangle> _triangles;
    };
}

#endif //TRIANGLESHAPE_HPP