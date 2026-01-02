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

#include "Geometry.hpp"

class ObjGeometry final : public QQuick3DGeometry {
    Q_OBJECT
   public:
    explicit ObjGeometry(QQuick3DObject *parent = nullptr);

    void setMesh(const std::vector<Vector3> &vertices,
                 const std::vector<Vector3> &normals,
                 const std::vector<TextureCoordinate> &textureCoords);
};

#endif  // MODELVIEWER_OBJGEOMETRY_HPP
