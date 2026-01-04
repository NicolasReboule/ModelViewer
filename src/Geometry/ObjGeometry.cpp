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
    const bool hasNormals = !normals.empty();
    const bool hasTextureCoords = !textureCoords.empty();
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
        const Vector3 &vertex = vertices[i];
        *vertexDataPointer++ = vertex.x;
        *vertexDataPointer++ = vertex.y;
        *vertexDataPointer++ = vertex.z;
        if (hasNormals) {
            const Vector3 &normal = normals[i];
            *vertexDataPointer++ = normal.x;
            *vertexDataPointer++ = normal.y;
            *vertexDataPointer++ = normal.z;
        }
        if (hasTextureCoords) {
            const TextureCoordinate &textureCoord = textureCoords[i];
            *vertexDataPointer++ = textureCoord.u;
            *vertexDataPointer++ = textureCoord.v;
        }
    }
    int stride = 3 * sizeof(float);
    int offset = 0;
    static int i = 0;
    addAttribute(Attribute::PositionSemantic, offset, Attribute::F32Type);
    offset += 3 * sizeof(float);
    if (hasNormals) {
        stride += 3 * sizeof(float);
        addAttribute(Attribute::NormalSemantic, offset, Attribute::F32Type);
        offset += 3 * sizeof(float);
    }
    if (hasTextureCoords) {
        stride += 2 * sizeof(float);
        addAttribute(Attribute::TexCoord0Semantic, offset, Attribute::F32Type);
        offset += 2 * sizeof(float);
    }
    setStride(stride);
    setVertexData(vertexData);
    setPrimitiveType(PrimitiveType::Triangles);
    update();
}

}  // namespace model_viewer::geometry
