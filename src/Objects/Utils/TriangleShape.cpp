/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ${descriptor}
*/

#include <cfloat>

#include "TriangleShape.hpp"

namespace RayTracer {
    std::optional<HitInfo> TriangleShape::hits(Ray const &ray)
    {
        auto bestT = DBL_MAX;
        HitInfo bestHit{};
        bool hit = false;

        for (auto &tri: _triangles) {
            auto result = tri.hits(ray);
            if (result.has_value() && result->hitDist < bestT) {
                bestT = result->hitDist;
                bestHit = result.value();
                hit = true;
            }
        }
        return hit ? std::optional(bestHit) : std::nullopt;
    }
}
