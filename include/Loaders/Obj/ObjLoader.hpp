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

/**
 * @brief Class for loading OBJ models
 */
class ObjLoader final : public ILoader {
   private:
    //! Vertices of the model
    std::vector<geometry::Vector3> _vertices;

    //! Texture coordinates of the model
    std::vector<geometry::TextureCoordinate> _textureCoords;

    //! Normals of the model
    std::vector<geometry::Vector3> _normals;

    //! Faces of the model
    std::vector<geometry::FaceIndex> _faces;

    //! Path to the model file
    std::string _modelPath;

    //! Map of parsing functions for different OBJ line prefixes
    std::unordered_map<std::string, std::function<void(const std::string &)>>
        _parseFunctions;

    //! Geometry of the model
    std::unique_ptr<geometry::ObjGeometry> _geometry;

    //! Material of the model
    std::unique_ptr<material::MTLMaterial> _material;

   public:
    //! Constructor
    ObjLoader();

    //! Destructor
    ~ObjLoader() override = default;

    /**
     * @brief Load an OBJ model from a file
     * @param filepath Path to the OBJ file
     * @todo Optimize parsing of the model
     * @todo Add support for groups and multiple materials
     */
    void loadModel(const std::string &filepath) override;

    /**
     * @brief Get the geometry of the loaded model
     * @return Geometry of the loaded model
     */
    QQuick3DGeometry *geometry() const override { return _geometry.get(); };

    /**
     * @brief Get the material of the loaded model
     * @return Material of the loaded model
     */
    material::MTLMaterial *material() const override {
        return _material.get();
    };

   private:
    //! Reset the OBJ loader state
    void resetObj();

    /**
     * @brief Parse a vertice line from the OBJ file
     * @param line Line to parse
     */
    void parseVertice(const std::string &line);

    /**
     * @brief Parse a normal vertice line from the OBJ file
     * @param line Line to parse
     */
    void parseNormal(const std::string &line);

    /**
     * @brief Parse a texture coordinate vertice line from the OBJ file
     * @param line Line to parse
     */
    void parseTextureCoordinate(const std::string &line);

    /**
     * @brief Parse a face line from the OBJ file
     * @param line Line to parse
     */
    void parseFace(const std::string &line);

    /**
     * @brief Parse a face index token from the OBJ file
     * @param token Token to parse
     * @return Parsed FaceIndex struct
     */
    geometry::FaceIndex parseFaceIndex(const std::string &token);

    /**
     * @brief Retrieve material from a material library line and call material's
     * parsing method
     * @param line Line to parse
     */
    void retrieveMaterial(const std::string &line);
};

}  // namespace model_viewer::loaders

#endif  // MODELVIEWER_OBJ_LOADER_HPP
