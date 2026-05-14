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
    #include <filesystem>
    #include <array>
    #include <string>
    #include <optional>
    #include <memory>

    #include "IObject.hpp"
    #include "Material.hpp"
    #include "ObjMaterialLibrary.hpp"
    #include "Vector.hpp"
    #include "Texture.hpp"
    #include "data/BoundingBox.hpp"
    #include "data/Vertex.hpp"
    #include "data/VertexNormal.hpp"
    #include "data/VertexTexture.hpp"
    #include "data/Face.hpp"
    #include "data/Triangle.hpp"

namespace RayTracer {
    class Model : public IObject {
    public:
        Model(const Maths::Point3D &position,
            const std::string &path, Material material, double scale);

        std::optional<HitInfo> hits(const Ray &ray) override;

        void addVertex(std::istringstream &line);

        void addVertexNormal(std::istringstream &line);

        void addVertexTexture(std::istringstream &line);

        void addFace(std::istringstream &line);

        void addMaterialLibrary(std::istringstream &line);

        void useMaterial(std::istringstream &line);

    private:
        static int normalizeIndex(int index, int size) noexcept;

        void parseFile(const std::string &path);

        void validateFace(FaceIndex &index) const;

        void triangulateFace(Face face);

        Material buildCurrentMaterial() const;
        std::optional<std::string> resolveCurrentTexturePath() const;
        std::optional<std::reference_wrapper<const Texture>>
        getOrLoadTexture(const std::string &path);
        std::optional<std::reference_wrapper<const Texture>>
        buildCurrentTexture();
        std::optional<std::array<Maths::Vector3D, 3>> buildTriangleTexCoords(
            const std::vector<FaceIndex> &indices,
            const std::array<size_t, 3> &tri) const;

        Maths::Point3D _pos;
        Material _material;
        std::vector<Vertex> _vertices;
        std::vector<VertexNormal> _normals;
        std::vector<VertexTexture> _texturesPos;
        std::vector<Triangle> _triangles;
        BoundingBox _boundingBox;
        std::vector<std::string> _texturePaths;
        std::vector<std::unique_ptr<Texture>> _textures;
        ObjMaterialLibrary _materialLibrary;
        std::string _currentMaterialName;
        std::filesystem::path _sourcePath;
        double _scale;

        static const std::unordered_map<std::string, void (Model::*)(
            std::istringstream &)> LINE_PARSE_FUNCTION;
    };
};

#endif
