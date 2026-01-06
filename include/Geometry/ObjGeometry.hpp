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
   private:
    //! Whether the geometry contains normals
    bool _hasNormals = false;

    //! Whether the geometry contains texture coordinates
    bool _hasTextureCoords = false;

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

   private:
    /**
     * @brief Set the model data to the geometry
     * @param vertices Vertices of the model
     * @param normals Normals of the model
     * @param textureCoords Texture coordinates of the model
     */
    void setModelData(const std::vector<Vector3> &vertices,
                      const std::vector<Vector3> &normals,
                      const std::vector<TextureCoordinate> &textureCoords);

    //! Configure the vertex layout of the geometry based on the data
    void configureVertexLayout();
};

}  // namespace model_viewer::geometry

#endif  // MODELVIEWER_OBJGEOMETRY_HPP
