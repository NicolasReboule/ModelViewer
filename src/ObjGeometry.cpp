/*
** EPITECH PROJECT, 2025
** ObjGeometry.cpp
** File description:
** ObjGeometry.cpp
*/

#include "ObjGeometry.hpp"

ObjGeometry::ObjGeometry(QQuick3DObject *parent) : QQuick3DGeometry(parent) {}

void ObjGeometry::setMesh(const std::vector<Vector3> &vertices) {
    const QByteArray vertexData(
        reinterpret_cast<const char *>(vertices.data()),
        static_cast<qsizetype>(vertices.size() * sizeof(Vector3)));
    setVertexData(vertexData);
    setStride(3 * sizeof(float));
    addAttribute(Attribute::PositionSemantic, 0, Attribute::F32Type);
    setPrimitiveType(PrimitiveType::Triangles);
    update();
}
