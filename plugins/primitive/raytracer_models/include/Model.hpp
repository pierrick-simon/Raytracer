/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** a
*/

#ifndef PRIMITIVEMODEL_HPP
    #define PRIMITIVEMODEL_HPP

    #include <unordered_map>
    #include <vector>

    #include "IObject.hpp"
    #include "Material.hpp"
    #include "Vector.hpp"
    #include "data/Vertex.hpp"
    #include "data/VertexNormal.hpp"
    #include "data/VertexTexture.hpp"
    #include "data/Face.hpp"

namespace RayTracer {
    class Model : public IObject {
    public:
        Model(const Maths::Point3D &position,
            const std::string &path, Material material);

        std::optional<HitInfo> hits(const Ray &ray) override;

        void addVertex(std::istringstream &line);

        void addVertexNormal(std::istringstream &line);

        void addVertexTexture(std::istringstream &line);

        void addFace(std::istringstream &line);

    private:
        static int normalizeIndex(int index, int size) noexcept;

        void parseFile(const std::string &path);

        Maths::Point3D _pos;
        Material _material;
        std::vector<Vertex> _vertices;
        std::vector<VertexNormal> _normals;
        std::vector<VertexTexture> _texturesPos;
        std::vector<Face> _faces;

        static const std::unordered_map<std::string, void (Model::*)(
            std::istringstream &)> LINE_PARSE_FUNCTION;
    };
};

#endif
