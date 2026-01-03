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

#include "Geometry/ObjGeometry.hpp"
#include "Helpers/StringHelpers.hpp"
#include "Loaders/ILoader.hpp"
#include "Material/Material.hpp"

namespace model_viewer::loaders {

class ObjLoader final : public ILoader {
   private:
    std::vector<geometry::Vector3> _vertices;

    std::vector<geometry::TextureCoordinate> _textureCoords;

    std::vector<geometry::Vector3> _normals;

    std::vector<geometry::FaceIndex> _faces;

    std::string _modelPath;

    std::unordered_map<std::string, std::function<void(const std::string &)>>
        _parseFunctions;

    std::unique_ptr<geometry::ObjGeometry> _geometry;

    std::unique_ptr<material::MTLMaterial> _material;

   public:
    ObjLoader();

    ~ObjLoader() override = default;

    void loadModel(const std::string &filepath) override;

    QQuick3DGeometry *geometry() const override { return _geometry.get(); };

    material::MTLMaterial *material() const override {
        return _material.get();
    };

   private:
    void resetObj();

    void parseVertice(const std::string &line);

    void parseNormal(const std::string &line);

    void parseTextureCoordinate(const std::string &line);

    void parseFace(const std::string &line);

    geometry::FaceIndex parseFaceIndex(const std::string &token);

    void retrieveMaterial(const std::string &line);
};

}  // namespace model_viewer::loaders

#endif  // MODELVIEWER_OBJ_LOADER_HPP
