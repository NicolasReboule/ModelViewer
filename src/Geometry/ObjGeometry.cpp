/*
** EPITECH PROJECT, 2025
** ObjGeometry.cpp
** File description:
** ObjGeometry.cpp
*/

#include "Geometry/ObjGeometry.hpp"

namespace model_viewer::geometry {

ObjGeometry::ObjGeometry(QQuick3DObject *parent) : QQuick3DGeometry(parent) {}

void ObjGeometry::setMesh(const std::vector<Vector3> &vertices,
                          const std::vector<Vector3> &normals,
                          const std::vector<TextureCoordinate> &textureCoords) {
    clear();
    _hasNormals = !normals.empty();
    _hasTextureCoords = !textureCoords.empty();
    setModelData(vertices, normals, textureCoords);
    configureVertexLayout();
    update();
}

void ObjGeometry::setModelData(
    const std::vector<Vector3> &vertices, const std::vector<Vector3> &normals,
    const std::vector<TextureCoordinate> &textureCoords) {
    QByteArray vertexData;

    const qsizetype vertexSize = static_cast<qsizetype>(vertices.size()) *
                                 static_cast<qsizetype>(sizeof(Vector3));
    const qsizetype normalSize = static_cast<qsizetype>(normals.size()) *
                                 static_cast<qsizetype>(sizeof(Vector3));
    const qsizetype textureSize =
        static_cast<qsizetype>(textureCoords.size()) *
        static_cast<qsizetype>(sizeof(TextureCoordinate));
    vertexData.resize(vertexSize + normalSize + textureSize);
    float *vertexDataPointer = reinterpret_cast<float *>(vertexData.data());
    for (size_t i = 0; i < vertices.size(); ++i) {
        const auto &[vx, vy, vz] = vertices[i];
        *vertexDataPointer++ = vx;
        *vertexDataPointer++ = vy;
        *vertexDataPointer++ = vz;
        if (_hasNormals) {
            const auto &[nx, ny, nz] = normals[i];
            *vertexDataPointer++ = nx;
            *vertexDataPointer++ = ny;
            *vertexDataPointer++ = nz;
        }
        if (_hasTextureCoords) {
            const auto &[u, v] = textureCoords[i];
            *vertexDataPointer++ = u;
            *vertexDataPointer++ = v;
        }
    }
    setVertexData(vertexData);
}

void ObjGeometry::configureVertexLayout() {
    int stride = 3 * sizeof(float);
    int offset = 0;
    addAttribute(Attribute::PositionSemantic, offset, Attribute::F32Type);
    offset += 3 * sizeof(float);
    if (_hasNormals) {
        stride += 3 * sizeof(float);
        addAttribute(Attribute::NormalSemantic, offset, Attribute::F32Type);
        offset += 3 * sizeof(float);
    }
    if (_hasTextureCoords) {
        stride += 2 * sizeof(float);
        addAttribute(Attribute::TexCoord0Semantic, offset, Attribute::F32Type);
        offset += 2 * sizeof(float);
    }
    setStride(stride);
    setPrimitiveType(PrimitiveType::Triangles);
}

}  // namespace model_viewer::geometry
