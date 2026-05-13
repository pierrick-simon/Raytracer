/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#ifndef FACE_HPP
    #define FACE_HPP
    #include <vector>
    #include <istream>

namespace RayTracer {
    struct FaceIndex {
        int v;
        int vt;
        int vn;
    };

    class Face {
    public:
        [[nodiscard]] const std::vector<FaceIndex> &getIndices() const noexcept;

        std::vector<FaceIndex> &getIndices() noexcept;

        void addIndex(const FaceIndex &index);

    private:
        std::vector<FaceIndex> _indices;
    };

    std::istream &operator>>(std::istream &stream, FaceIndex &index);
    std::istream &operator>>(std::istream &stream, Face &face);
} // RayTracer

#endif
