/*
** EPITECH PROJECT, 2025
** Obj.cpp
** File description:
** Obj.cpp
*/

#include "Loaders/Obj/ObjLoader.hpp"

#include <QFileInfo>

namespace model_viewer::loaders {

ObjLoader::ObjLoader()
    : _geometry(std::make_unique<geometry::ObjGeometry>()),
      _material(std::make_unique<material::MTLMaterial>()) {
    _parseFunctions = {
        {"v", [this](const std::string &l) { parseVertice(l); }},
        {"vn", [this](const std::string &l) { parseNormal(l); }},
        {"vt", [this](const std::string &l) { parseTextureCoordinate(l); }},
        {"f", [this](const std::string &l) { parseFace(l); }},
        {"mtllib", [this](const std::string &l) { retrieveMaterial(l); }},
    };
}

// TODO: Optimize
// TODO: Add groups and multiple materials
void ObjLoader::loadModel(const std::string &filepath) {
    resetObj();
    _material->resetMaterial();

    _modelPath = string_helpers::normalizePath(filepath);
    std::ifstream in(_modelPath, std::ios::in);
    if (!in.is_open()) {
        std::cerr << "ObjLoader: Could not open file " << _modelPath << ": "
                  << std::strerror(errno) << std::endl;
        return;
    }
    std::string line;
    while (std::getline(in, line)) {
        const auto pos = line.find(' ');
        const std::string lineStart =
            string_helpers::trim_copy(line.substr(0, pos));
        if (_parseFunctions.contains(lineStart))
            _parseFunctions.at(lineStart)(line);
    }

    std::vector<geometry::Vector3> v;
    std::vector<geometry::TextureCoordinate> vt;
    std::vector<geometry::Vector3> vn;
    for (auto f : _faces) {
        if (!_vertices.empty() && f.v != 0) {
            const int vIdx = f.v > 0 ? f.v - 1 : _vertices.size() + f.v;
            v.push_back(_vertices[vIdx]);
        }
        if (!_textureCoords.empty() && f.vt != 0) {
            const int vtIdx = f.vt > 0 ? f.vt - 1 : _vertices.size() + f.vt;
            vt.push_back(_textureCoords[vtIdx]);
        }
        if (!_normals.empty() && f.vn != 0) {
            const int vnIdx = f.vn > 0 ? f.vn - 1 : _vertices.size() + f.vn;
            vn.push_back(_normals[vnIdx]);
        }
    }
    _vertices = v;
    _textureCoords = vt;
    _normals = vn;
    _geometry->setMesh(_vertices, _normals, _textureCoords);
}

void ObjLoader::resetObj() {
    _faces.clear();
    _vertices.clear();
    _normals.clear();
    _textureCoords.clear();
}

void ObjLoader::parseVertice(const std::string &line) {
    float x, y, z;  // Missing optional w
    if (std::sscanf(line.c_str() + 2, "%f %f %f", &x, &y, &z) < 3)
        std::cerr << "Invalid vertice at line " << line << std::endl;
    else
        this->_vertices.push_back({x, y, z});
}

void ObjLoader::parseNormal(const std::string &line) {
    float x, y, z;
    if (std::sscanf(line.c_str() + 2, "%f %f %f", &x, &y, &z) < 3)
        std::cerr << "Invalid normal at line " << line << std::endl;
    else
        this->_normals.push_back({x, y, z});
}

void ObjLoader::parseTextureCoordinate(const std::string &line) {
    float u, v;  // Missing w
    if (std::sscanf(line.c_str() + 2, "%f %f", &u, &v) < 2)
        std::cerr << "Invalid normal at line " << line << std::endl;
    else
        this->_textureCoords.push_back({u, v});
}

void ObjLoader::parseFace(const std::string &line) {
    std::istringstream f(line.substr(2));
    std::string token;
    std::vector<geometry::FaceIndex> face;
    while (f >> token) face.push_back(parseFaceIndex(token));
    for (size_t i = 1; i + 1 < face.size(); ++i) {
        this->_faces.push_back(face[0]);
        this->_faces.push_back(face[i]);
        this->_faces.push_back(face[i + 1]);
    }
}

geometry::FaceIndex ObjLoader::parseFaceIndex(const std::string &token) {
    geometry::FaceIndex idx;
    std::sscanf(token.c_str(), "%d/%d/%d", &idx.v, &idx.vt, &idx.vn);

    if (token.find("//") != std::string::npos) {
        std::sscanf(token.c_str(), "%d//%d", &idx.v, &idx.vn);
        idx.vt = 0;
    } else if (token.find('/') != std::string::npos &&
               std::ranges::count(token, '/') == 1) {
        std::sscanf(token.c_str(), "%d/%d", &idx.v, &idx.vt);
        idx.vn = 0;
    } else if (token.find('/') == std::string::npos) {
        std::sscanf(token.c_str(), "%d", &idx.v);
    }
    return idx;
}

void ObjLoader::retrieveMaterial(const std::string &line) {
    const std::string name =
        string_helpers::trim_copy(line.substr(sizeof("mtllib")));
    const std::filesystem::path path =
        std::filesystem::path(_modelPath).parent_path() / name;
    _material->parseMTL(path.string());
}

}  // namespace model_viewer::loaders
