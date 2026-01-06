/*
** EPITECH PROJECT, 2026
** Material.cpp
** File description:
** Material.cpp
*/

#include "Material/Material.hpp"

namespace model_viewer::material {

MTLMaterial::MTLMaterial(QObject *parent) : QObject(parent) {
    _parseFunctions = {
        {"Ka", [this](const std::string &l,
                      const std::string &k) { parseColor(l, k); }},
        {"Kd", [this](const std::string &l,
                      const std::string &k) { parseColor(l, k); }},
        {"Ks", [this](const std::string &l,
                      const std::string &k) { parseColor(l, k); }},
        {"Ke", [this](const std::string &l,
                      const std::string &k) { parseColor(l, k); }},
        {"Tf", [this](const std::string &l,
                      const std::string &k) { parseColor(l, k); }},
        {"illum", [this](const std::string &l,
                         const std::string &k) { parseScalar(l, k); }},
        {"d", [this](const std::string &l,
                     const std::string &k) { parseScalar(l, k); }},
        {"sharpness", [this](const std::string &l,
                             const std::string &k) { parseScalar(l, k); }},
        {"Ni", [this](const std::string &l,
                      const std::string &k) { parseScalar(l, k); }},
        {"map_Ka", [this](const std::string &l,
                          const std::string &k) { parseMap(l, k); }},
        {"map_Kd", [this](const std::string &l,
                          const std::string &k) { parseMap(l, k); }},
        {"map_Ks", [this](const std::string &l,
                          const std::string &k) { parseMap(l, k); }},
        {"map_Ns", [this](const std::string &l,
                          const std::string &k) { parseMap(l, k); }},
        {"map_Ke", [this](const std::string &l,
                          const std::string &k) { parseMap(l, k); }},
        {"bump", [this](const std::string &l,
                        const std::string &k) { parseMap(l, k); }},
        {"decal", [this](const std::string &l,
                         const std::string &k) { parseMap(l, k); }},
        {"disp", [this](const std::string &l,
                        const std::string &k) { parseMap(l, k); }},
    };
}

void MTLMaterial::parseMTL(const std::string &filepath) {
    std::ifstream in(filepath);
    if (!in.is_open()) {
        std::cerr << "MTLMaterial: Could not open file " << filepath << ": "
                  << std::strerror(errno) << std::endl;
        return;
    }
    _parentPath = std::filesystem::path(filepath).parent_path();
    parseMaterial(in);
    setMaterialValues();
}

void MTLMaterial::parseMaterial(std::ifstream &file) {
    std::string line;
    while (std::getline(file, line)) {
        const auto pos = line.find(' ');
        const std::string lineStart =
            string_helpers::trim_copy(line.substr(0, pos));
        if (_parseFunctions.contains(lineStart))
            _parseFunctions.at(lineStart)(line, lineStart);
    }
}

void MTLMaterial::resetMaterial() {
    _scalars.clear();
    _colors.clear();
    _maps.clear();
    _scalars["d"] = 1.0;
    _scalars["illum"] = 1.0;
    _colors["Kd"] = QColor(255, 255, 255);
    setMaterialValues();
}

void MTLMaterial::setMaterialValues() {
    _Ka = _colors["Ka"];
    _Kd = _colors["Kd"];
    _Ks = _colors["Ks"];
    _Tf = _colors["Tf"];
    _Ke = _colors["ke"];

    _illumination = _scalars["illum"];
    _d = _scalars["d"];
    _Ns = _scalars["Ns"];
    _sharpness = _scalars["sharpness"];
    _Ni = _scalars["Ni"];

    _ambientMap = _maps["map_Ka"];
    _diffuseMap = _maps["map_Kd"];
    _specularReflectionMap = _maps["map_Ks"];
    _specularMap = _maps["map_Ns"];
    _emissiveMap = _maps["map_Ke"];
    _dissolveMap = _maps["map_d"];
    _bumpMap = _maps["bump"];
    _decalMap = _maps["decal"];
    _dispersionMap = _maps["disp"];

    _roughness = std::clamp(1.0 - std::pow(_Ns / 100.0, 0.25), 0.04, 1.0);
    _metalness =
        std::clamp((_Ks.red() + _Ks.green() + _Ks.blue()) / 3.0, 0.0, 1.0);
}

void MTLMaterial::parseScalar(const std::string &line, const std::string &key) {
    float scalar;
    const std::string lineTrimmed =
        string_helpers::trim_copy(line.substr(key.size() + 1));
    if (std::sscanf(lineTrimmed.c_str(), "%f", &scalar) < 1)
        std::cerr << "Invalid scalar at line " << line << std::endl;
    else
        _scalars[key] = scalar;
}

void MTLMaterial::parseColor(const std::string &line, const std::string &key) {
    float r, g, b;
    const std::string lineTrimmed =
        string_helpers::trim_copy(line.substr(key.size() + 1));
    if (std::sscanf(lineTrimmed.c_str(), "%f %f %f", &r, &g, &b) < 3)
        std::cerr << "Invalid color at line " << line << std::endl;
    else
        _colors[key] = {static_cast<int>(r * 255), static_cast<int>(g * 255),
                        static_cast<int>(b * 255)};
}

void MTLMaterial::parseMap(const std::string &line, const std::string &key) {
    const std::string map =
        string_helpers::trim_copy(line.substr(key.size() + 1));
    if (map.empty()) std::cerr << "Empty map at line " << line << std::endl;
    const std::string mapPath = (_parentPath / map).string();
    _maps[key] = QUrl::fromLocalFile(mapPath.c_str());
}

}  // namespace model_viewer::material
