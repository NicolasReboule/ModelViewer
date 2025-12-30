/*
** EPITECH PROJECT, 2025
** Obj.hpp
** File description:
** Obj.hpp
*/

#ifndef MODELVIEWER_OBJ_LOADER_HPP
#define MODELVIEWER_OBJ_LOADER_HPP

#include <fstream>
#include <iostream>
#include <memory>

#include "ILoader.hpp"
#include "ObjGeometry.hpp"

class ObjLoader final : public ILoader {
   private:
    std::vector<Vector3> _vertices;
    std::vector<float> _textureCoords;
    std::vector<Vector3> _normals;
    std::vector<FaceIndex> _faces;
    std::unordered_map<std::string, std::function<void(const std::string &)>>
        _parseFunctions;
    std::unique_ptr<ObjGeometry> _geometry;

   public:
    ObjLoader();

    ~ObjLoader() override = default;

    void loadModel(const std::string &filepath) override;

    QQuick3DGeometry *geometry() const override { return _geometry.get(); }

   private:
    void parseVertice(const std::string &line);

    void parseNormal(const std::string &line);

    void parseTextureCoordinate(const std::string &line);

    void parseFace(const std::string &line);

    FaceIndex parseFaceIndex(const std::string &token);
};

#endif  // MODELVIEWER_OBJ_LOADER_HPP
