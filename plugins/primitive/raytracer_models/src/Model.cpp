/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** DisplaySFML
*/

#include <utility>
#include <sstream>
#include <fstream>

#include "Model.hpp"

namespace RayTracer {
    Model::Model(const Maths::Point3D &position, const std::string &path,
        Material material):
        _pos(position),
        _material(std::move(material))
    {
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
    }

    void Model::addFace(std::istringstream &line)
    {
        Face face;

        line >> face;
        if (!line.eof() || line.bad() || face.getIndices().size() < 3)
            throw std::invalid_argument("Invalid face line");

        for (auto &index : face.getIndices()) {
            index.v = normalizeIndex(index.v, static_cast<int>(_vertices.size()));
            index.vt = normalizeIndex(index.vt, static_cast<int>(_texturesPos.size()));
            index.vn = normalizeIndex(index.vn, static_cast<int>(_normals.size()));

            if (index.v < 0 || index.v >= static_cast<int>(_vertices.size()))
                throw std::invalid_argument("Face vertex index out of range");
            if (index.vt < -1 || index.vt >= static_cast<int>(_texturesPos.size()))
                throw std::invalid_argument("Face texture index out of range");
            if (index.vn < -1 || index.vn >= static_cast<int>(_normals.size()))
                throw std::invalid_argument("Face normal index out of range");
        }
        this->_faces.push_back(face);
    }

    const std::unordered_map<std::string, void (Model::*)(
            std::istringstream &)> Model::LINE_PARSE_FUNCTION = {
        {"v", &Model::addVertex},
        {"vt", &Model::addVertexTexture},
        {"vn", &Model::addVertexNormal},
        {"f", &Model::addFace},
    };
}
