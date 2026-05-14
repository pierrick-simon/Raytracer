/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DisplaySFML
*/

#include <utility>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <optional>
#include <algorithm>
#include <cctype>

#include "Model.hpp"
#include "TriangulationData.hpp"

namespace RayTracer {
    namespace {
        Maths::Point3D toPoint(const Vertex &vertex,
            const Maths::Point3D &offset)
        {
            return Maths::Point3D{
                vertex.getX() + offset.getX(),
                vertex.getY() + offset.getY(),
                vertex.getZ() + offset.getZ()
            };
        }

        std::string toLower(std::string value)
        {
            for (char &ch : value)
                ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
            return value;
        }

        bool isPpmTexture(const std::string &path)
        {
            std::filesystem::path fsPath(path);
            return toLower(fsPath.extension().string()) == ".ppm";
        }

        std::vector<Maths::Point3D> buildPolygonPoints(
            const std::vector<FaceIndex> &indices,
            const std::vector<Vertex> &vertices)
        {
            std::vector<Maths::Point3D> polygon;
            Maths::Point3D offset{};

            polygon.reserve(indices.size());
            for (const auto &index: indices)
                polygon.push_back(toPoint(vertices[index.v], offset));
            return polygon;
        }
    }

    Model::Model(const Maths::Point3D &position, const std::string &path,
        Material material, double scale) :
        _pos(position),
        _material(std::move(material)),
        _scale(scale)
    {
        this->parseFile(path);
    }

    std::optional<HitInfo> Model::hits(const Ray &ray)
    {
        std::optional<HitInfo> bestHit;

        if (!this->_boundingBox.hits(ray))
            return std::nullopt;

        for (const auto &triangle: this->_triangles) {
            auto hit = triangle.hits(ray);
            if (!hit)
                continue;
            hit->material = this->_material;
            if (!bestHit || hit->hitDist < bestHit->hitDist)
                bestHit = hit;
        }
        return bestHit;
    }

    void Model::addVertex(std::istringstream &line)
    {
        Vertex newVertex{};
        line >> newVertex;
        if (!line)
            throw std::invalid_argument("Invalid vertex line");
        line >> std::ws;
        if (!line.eof())
            throw std::invalid_argument("Invalid vertex line");
        newVertex *= this->_scale;
        this->_vertices.push_back(newVertex);
    }

    void Model::addVertexNormal(std::istringstream &line)
    {
        VertexNormal newVertex{};

        line >> newVertex;
        if (!line)
            throw std::invalid_argument("Invalid vertex normal line");
        line >> std::ws;
        if (!line.eof())
            throw std::invalid_argument("Invalid vertex normal line");
        this->_normals.push_back(newVertex);
    }

    void Model::addVertexTexture(std::istringstream &line)
    {
        VertexTexture newVertex{};

        line >> newVertex;
        if (!line)
            throw std::invalid_argument("Invalid vertex texture line");
        line >> std::ws;
        if (!line.eof())
            throw std::invalid_argument("Invalid vertex texture line");
        this->_texturesPos.push_back(newVertex);
    }

    void Model::addFace(std::istringstream &line)
    {
        Face face;

        line >> face;
        if (!line.eof() || line.bad() || face.getIndices().size() < 3)
            throw std::invalid_argument("Invalid face line");

        for (auto &index: face.getIndices())
            this->validateFace(index);
        triangulateFace(face);
    }

    void Model::addMaterialLibrary(std::istringstream &line)
    {
        std::string filename;
        bool hasFilename = false;

        while (line >> filename) {
            hasFilename = true;
            std::filesystem::path materialPath = filename;
            if (!this->_sourcePath.empty())
                materialPath = this->_sourcePath.parent_path() / materialPath;
            this->_materialLibrary.parseFile(materialPath.string());
        }
        if (!hasFilename)
            throw std::invalid_argument("Invalid mtllib line");
    }

    void Model::useMaterial(std::istringstream &line)
    {
        std::string name;

        line >> name;
        if (!line)
            throw std::invalid_argument("Invalid usemtl line");
        line >> std::ws;
        if (!line.eof())
            throw std::invalid_argument("Invalid usemtl line");
        this->_currentMaterialName = name;
    }

    int Model::normalizeIndex(int index, int size) noexcept
    {
        if (index > 0)
            return index - 1;
        if (index < 0)
            return size + index;
        return -1;
    }

    void Model::parseFile(const std::string &path)
    {
        std::ifstream file(path);

        if (!file.is_open())
            throw std::invalid_argument("The given path is not a valid file");
        this->_sourcePath = std::filesystem::path(path);
        std::string line;
        while (std::getline(file, line)) {
            std::string cleanedLine = line.substr(0, line.find('#'));
            std::istringstream iss(cleanedLine);
            iss >> std::ws;
            if (iss.eof())
                continue;
            std::string command;
            iss >> command;
            if (!iss || iss.eof())
                throw std::invalid_argument("The given command is not a valid");
            auto it = LINE_PARSE_FUNCTION.find(command);
            if (it != LINE_PARSE_FUNCTION.end())
                (this->*it->second)(iss);
        }
        this->_boundingBox = BoundingBox::fromVertices(this->_vertices,
            this->_pos);
    }

    void Model::validateFace(FaceIndex &index) const
    {
        int verticesSize = static_cast<int>(this->_vertices.size());
        int texturesSize = static_cast<int>(this->_texturesPos.size());
        int normalsSize = static_cast<int>(this->_normals.size());

        index.v = normalizeIndex(index.v, verticesSize);
        index.vt = normalizeIndex(index.vt, texturesSize);
        index.vn = normalizeIndex(index.vn, normalsSize);

        if (index.v < 0 || index.v >= verticesSize)
            throw std::invalid_argument("Face vertex index out of range");
        if (index.vt < -1 || index.vt >= texturesSize)
            throw std::invalid_argument("Face texture index out of range");
        if (index.vn < -1 || index.vn >= normalsSize)
            throw std::invalid_argument("Face normal index out of range");
    }

    void Model::triangulateFace(Face face)
    {
        auto polygon = buildPolygonPoints(face.getIndices(), this->_vertices);
        TriangulationData triangulationData(polygon);
        if (!triangulationData.triangulate())
            return;

        auto triangles = triangulationData.getTriangles();
        if (triangles.empty())
            throw std::invalid_argument("Invalid face triangulation");

        const auto &indices = face.getIndices();
        for (const auto &tri: triangles) {
            const auto texCoords = this->buildTriangleTexCoords(indices, tri);
            std::optional<std::reference_wrapper<const Texture>> texture;

            if (texCoords)
                texture = this->buildCurrentTexture();

            const Maths::Point3D a = toPoint(this->_vertices[indices[tri[0]].v], this->_pos);
            const Maths::Point3D b = toPoint(this->_vertices[indices[tri[1]].v], this->_pos);
            const Maths::Point3D c = toPoint(this->_vertices[indices[tri[2]].v], this->_pos);

            this->_triangles.emplace_back(a, b, c, texture, texCoords);
        }
    }

    Material Model::buildCurrentMaterial() const
    {
        if (this->_currentMaterialName.empty())
            return this->_material;

        const auto *materialData = this->_materialLibrary.findMaterial(
            this->_currentMaterialName);
        if (!materialData)
            return this->_material;

        const double specular =
        (materialData->specular.getR()
         + materialData->specular.getG()
         + materialData->specular.getB()) / 3.0;

        return Material::Builder()
            .color(materialData->diffuse)
            .metallic(materialData->metallic)
            .specular(specular)
            .roughness(materialData->roughness)
            .opacity(materialData->opacity)
            .refraction(materialData->refraction)
            .build();
    }

    std::optional<std::string> Model::resolveCurrentTexturePath() const
    {
        if (this->_currentMaterialName.empty())
            return std::nullopt;

        const auto *materialData = this->_materialLibrary.findMaterial(
            this->_currentMaterialName);
        if (!materialData)
            return std::nullopt;

        auto textureIt = materialData->textures.find("map_Kd");
        if (textureIt == materialData->textures.end())
            return std::nullopt;

        const std::string &path = textureIt->second;
        if (!isPpmTexture(path))
            return std::nullopt;

        return path;
    }

    std::optional<std::reference_wrapper<const Texture>>
    Model::getOrLoadTexture(const std::string &path)
    {
        auto existing = std::find(this->_texturePaths.begin(),
            this->_texturePaths.end(), path);
        if (existing != this->_texturePaths.end()) {
            const size_t index = static_cast<size_t>(
                std::distance(this->_texturePaths.begin(), existing));
            return std::cref(*this->_textures[index]);
        }

        this->_texturePaths.push_back(path);
        this->_textures.emplace_back(std::make_unique<Texture>(path));
        return std::cref(*this->_textures.back());
    }

    std::optional<std::reference_wrapper<const Texture>>
    Model::buildCurrentTexture()
    {
        auto path = this->resolveCurrentTexturePath();
        if (!path)
            return std::nullopt;

        return this->getOrLoadTexture(*path);
    }

    std::optional<std::array<Maths::Vector3D, 3>>
    Model::buildTriangleTexCoords(const std::vector<FaceIndex> &indices,
        const std::array<size_t, 3> &tri) const
    {
        if (indices[tri[0]].vt < 0 || indices[tri[1]].vt < 0
            || indices[tri[2]].vt < 0)
            return std::nullopt;

        const auto &vt0 = this->_texturesPos[indices[tri[0]].vt];
        const auto &vt1 = this->_texturesPos[indices[tri[1]].vt];
        const auto &vt2 = this->_texturesPos[indices[tri[2]].vt];

        std::array<Maths::Vector3D, 3> coords{
            Maths::Vector3D{vt0[0], vt0[1], vt0[2]},
            Maths::Vector3D{vt1[0], vt1[1], vt1[2]},
            Maths::Vector3D{vt2[0], vt2[1], vt2[2]}
        };
        return coords;
    }

    const std::unordered_map<std::string, void (Model::*)(
        std::istringstream &)> Model::LINE_PARSE_FUNCTION = {
        {"v", &Model::addVertex},
        {"vt", &Model::addVertexTexture},
        {"vn", &Model::addVertexNormal},
        {"f", &Model::addFace},
        {"mtllib", &Model::addMaterialLibrary},
        {"usemtl", &Model::useMaterial},
    };
}
