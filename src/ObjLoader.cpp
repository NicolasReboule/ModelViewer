/*
** EPITECH PROJECT, 2025
** Obj.cpp
** File description:
** Obj.cpp
*/

#include "ObjLoader.hpp"

ObjLoader::ObjLoader() : _geometry(new ObjGeometry()) {
    _parseFunctions = {
        {"v ", [this](const std::string &l) { parseVertice(l); }},
        {"vn", [this](const std::string &l) { parseNormal(l); }},
        {"vt", [this](const std::string &l) { parseTextureCoordinate(l); }},
        {"f ", [this](const std::string &l) { parseFace(l); }},
    };
}

// TODO: Optimize
void ObjLoader::loadModel(const std::string &filepath) {
    _faces.clear();
    _vertices.clear();
    _normals.clear();
    _textureCoords.clear();

    std::ifstream in(filepath);
    if (!in.is_open()) {
        std::cerr << "Could not open file " << filepath << std::endl;
        return;
    }
    std::string line;
    while (std::getline(in, line)) {
        std::string lineStart = line.substr(0, 2);
        if (_parseFunctions.contains(lineStart))
            _parseFunctions.at(lineStart)(line);
    }

    std::vector<Vector3> v;
    std::vector<float> vt;
    std::vector<Vector3> vn;
    for (auto f : _faces) {
        if (!_vertices.empty()) {
            const int vIdx = f.v > 0 ? f.v - 1 : v.size() + f.v;
            v.push_back(_vertices[vIdx]);
        }
        if (!_textureCoords.empty()) {
            const int vtIdx = f.vt > 0 ? f.vt - 1 : v.size() + f.vt;
            vt.push_back(_textureCoords[vtIdx]);
        }
        if (!_normals.empty()) {
            const int vnIdx = f.vn > 0 ? f.vn - 1 : v.size() + f.vn;
            vn.push_back(_normals[vnIdx]);
        }
    }
    _vertices = v;
    _textureCoords = vt;
    _normals = vn;
    _geometry->setMesh(_vertices);
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
    float u;  // Missing optional v and w
    if (std::sscanf(line.c_str() + 2, "%f", &u) < 1)
        std::cerr << "Invalid normal at line " << line << std::endl;
    else
        this->_textureCoords.push_back(u);
}

void ObjLoader::parseFace(const std::string &line) {
    std::istringstream f(line.substr(2));
    std::string token;
    std::vector<FaceIndex> face;
    while (f >> token) face.push_back(parseFaceIndex(token));
    for (size_t i = 1; i + 1 < face.size(); ++i) {
        this->_faces.push_back(face[0]);
        this->_faces.push_back(face[i]);
        this->_faces.push_back(face[i + 1]);
    }
}

FaceIndex ObjLoader::parseFaceIndex(const std::string &token) {
    FaceIndex idx;
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
