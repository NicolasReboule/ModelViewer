/*
** EPITECH PROJECT, 2025
** Obj.hpp
** File description:
** Obj.hpp
*/

#ifndef MODELVIEWER_OBJ_LOADER_HPP
#define MODELVIEWER_OBJ_LOADER_HPP

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>

#include "ILoader.hpp"
#include "Material.hpp"
#include "ObjGeometry.hpp"
#include "StringHelpers.hpp"

class ObjLoader final : public ILoader {
   private:
    std::vector<Vector3> _vertices;

    std::vector<TextureCoordinate> _textureCoords;

    std::vector<Vector3> _normals;

    std::vector<FaceIndex> _faces;

    std::string _modelPath;

    std::unordered_map<std::string, std::function<void(const std::string &)>>
        _parseFunctions;

    std::unique_ptr<ObjGeometry> _geometry;

    std::unique_ptr<MTLMaterial> _material;

   public:
    ObjLoader();

    ~ObjLoader() override = default;

    void loadModel(const std::string &filepath) override;

    QQuick3DGeometry *geometry() const override { return _geometry.get(); };

    MTLMaterial *material() const override { return _material.get(); };

   private:
    void resetObj();

    void parseVertice(const std::string &line);

    void parseNormal(const std::string &line);

    void parseTextureCoordinate(const std::string &line);

    void parseFace(const std::string &line);

    FaceIndex parseFaceIndex(const std::string &token);

    void retrieveMaterial(const std::string &line);
};

#endif  // MODELVIEWER_OBJ_LOADER_HPP
