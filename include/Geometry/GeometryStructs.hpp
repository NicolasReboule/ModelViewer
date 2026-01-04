/*
** EPITECH PROJECT, 2025
** Geometry.hpp
** File description:
** Geometry.hpp
*/

#ifndef MODELVIEWER_GEOMETRY_HPP
#define MODELVIEWER_GEOMETRY_HPP

namespace model_viewer::geometry {

/**
 * @brief Struct representing a 3D Vector
 */
struct Vector3 {
    //! X axis
    float x;
    //! Y axis
    float y;
    //! Z axis
    float z;
};

/**
 * @brief Struct representing a face's indexes in an OBJ model
 */
struct FaceIndex {
    //! Vertice index
    int v = 0;
    //! Texture coordinate vertice index
    int vt = 0;
    //! Normal vertice index
    int vn = 0;
};

/**
 * @brief Struct representing a texture coordinate in an OBJ model
 */
struct TextureCoordinate {
    //! Horizontal axis
    float u;
    //! Vertical axis
    float v;
};

}  // namespace model_viewer::geometry

#endif  // MODELVIEWER_GEOMETRY_HPP
