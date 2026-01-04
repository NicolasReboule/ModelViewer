/*
** EPITECH PROJECT, 2025
** ObjGeometry.hpp
** File description:
** ObjGeometry.hpp
*/

#ifndef MODELVIEWER_OBJGEOMETRY_HPP
#define MODELVIEWER_OBJGEOMETRY_HPP

#include <QObject>
#include <QQuick3DGeometry>
#include <sstream>

#include "GeometryStructs.hpp"

namespace model_viewer::geometry {

/**
 * @brief Class representing the geometry of an OBJ model
 */
class ObjGeometry final : public QQuick3DGeometry {
    Q_OBJECT
   public:
    /**
     * @brief Constructor
     * @param parent Parent QQuick3DObject, nullptr by default
     */
    explicit ObjGeometry(QQuick3DObject *parent = nullptr);

    /**
     * @brief Set the mesh data
     * @param vertices Vertices of the model
     * @param normals Normals of the model
     * @param textureCoords Texture coordinates of the model
     */
    void setMesh(const std::vector<Vector3> &vertices,
                 const std::vector<Vector3> &normals,
                 const std::vector<TextureCoordinate> &textureCoords);
};

}  // namespace model_viewer::geometry

#endif  // MODELVIEWER_OBJGEOMETRY_HPP
