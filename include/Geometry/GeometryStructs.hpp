/*
** EPITECH PROJECT, 2025
** Geometry.hpp
** File description:
** Geometry.hpp
*/

#ifndef MODELVIEWER_GEOMETRY_HPP
#define MODELVIEWER_GEOMETRY_HPP

namespace model_viewer::geometry {

struct Vector3 {
    float x;
    float y;
    float z;
};

struct FaceIndex {
    int v = 0;
    int vt = 0;
    int vn = 0;
};

struct TextureCoordinate {
    float u;
    float v;
};

}  // namespace model_viewer::geometry

#endif  // MODELVIEWER_GEOMETRY_HPP
