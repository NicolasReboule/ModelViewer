/*
** EPITECH PROJECT, 2026
** Material.hpp
** File description:
** Material.hpp
*/

#ifndef MODELVIEWER_MATERIAL_HPP
#define MODELVIEWER_MATERIAL_HPP

#include <QColor>
#include <QObject>
#include <QUrl>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "Geometry/GeometryStructs.hpp"
#include "Helpers/StringHelpers.hpp"

namespace model_viewer::material {

// TODO: Seek ways to improve this class' architecture
class MTLMaterial final : public QObject {
    Q_OBJECT
    Q_PROPERTY(QColor diffuseColor MEMBER _Kd NOTIFY KdChanged)

    Q_PROPERTY(
        qreal illumination MEMBER _illumination NOTIFY illuminationChanged)
    Q_PROPERTY(qreal metalness MEMBER _metalness NOTIFY metalnessChanged)
    Q_PROPERTY(qreal roughness MEMBER _roughness NOTIFY roughnessChanged)
    Q_PROPERTY(
        qreal bumpStrength MEMBER _bumpStrength NOTIFY bumpStrengthChanged)
    Q_PROPERTY(qreal opacity MEMBER _d NOTIFY dChanged)
    Q_PROPERTY(qreal indexOfRefraction MEMBER _Ni NOTIFY NiChanged)

    Q_PROPERTY(QUrl diffuseMap READ getDiffuseMap NOTIFY diffuseMapChanged)
    Q_PROPERTY(QUrl specularReflectionMap READ getSpecularReflectionMap NOTIFY
                   specularReflectionMapChanged)
    Q_PROPERTY(QUrl specularMap READ getSpecularMap NOTIFY specularMapChanged)
    Q_PROPERTY(QUrl emissiveMap READ getEmissiveMap NOTIFY emissiveMapChanged)
    Q_PROPERTY(QUrl dissolveMap READ getDissolveMap NOTIFY dissolveMapChanged)
    Q_PROPERTY(QUrl bumpMap READ getBumpMap NOTIFY bumpMapChanged)
   public:
   private:
    std::filesystem::path _parentPath;

    QColor _Ka;  // Ambient Color

    QColor _Kd;  // Diffuse Color -> diffuseColor

    QColor _Ks;  // Specular Color -> specularTint

    QColor _Ke;  // Emissive Factor -> emissiveFactor

    QColor _Tf;  // Transmission Filter

    qreal _illumination;  // lighting

    qreal _d;  // opacity

    qreal _Ns;  // specularRoughness

    qreal _sharpness;

    qreal _Ni;  // indexOfRefraction

    qreal _metalness = 0.0;

    qreal _roughness = 0.0;

    qreal _bumpStrength = 0.0;

    QUrl _ambientMap;  // map_Ka

    QUrl _diffuseMap;  // map_Kd -> diffuseMap

    QUrl _specularReflectionMap;  // map_Ks -> specularReflectionMap

    QUrl _specularMap;  // map_Ns -> specularMap

    QUrl _emissiveMap;  // map_Ke -> emissiveMap

    QUrl _dissolveMap;  // map_d -> opacityMap

    QUrl _bumpMap;  // bump -> bumpMap

    QUrl _decalMap;  // decal

    QUrl _dispersionMap;  // disp

    std::unordered_map<std::string, qreal> _scalars;

    std::unordered_map<std::string, QColor> _colors;

    std::unordered_map<std::string, QUrl> _maps;

    std::unordered_map<std::string, std::function<void(const std::string &,
                                                       const std::string &)>>
        _parseFunctions;

   public:
    explicit MTLMaterial(QObject *parent = nullptr);

    ~MTLMaterial() override = default;

    void parseMTL(const std::string &filepath);

    void resetMaterial();

    const QUrl &getAmbientMap() const { return _ambientMap; };

    const QUrl &getDiffuseMap() const { return _diffuseMap; };

    const QUrl &getSpecularReflectionMap() const {
        return _specularReflectionMap;
    };

    const QUrl &getSpecularMap() const { return _specularMap; };

    const QUrl &getEmissiveMap() const { return _emissiveMap; };

    const QUrl &getDissolveMap() const { return _dissolveMap; };

    const QUrl &getBumpMap() const { return _bumpMap; };

    const QUrl &getDecalMap() const { return _decalMap; };

    const QUrl &getDispersionMap() const { return _dispersionMap; };
   signals:
    void KdChanged();

    void illuminationChanged();

    void dChanged();

    void NsChanged();

    void sharpnessChanged();

    void NiChanged();

    void metalnessChanged();

    void roughnessChanged();

    void bumpStrengthChanged();

    void diffuseMapChanged();

    void specularReflectionMapChanged();

    void specularMapChanged();

    void emissiveMapChanged();

    void dissolveMapChanged();

    void bumpMapChanged();

   private:
    void setMaterialValues();

    void parseScalar(const std::string &line, const std::string &key);

    void parseColor(const std::string &line, const std::string &key);

    void parseMap(const std::string &line, const std::string &key);
};

}  // namespace model_viewer::material

#endif  // MODELVIEWER_MATERIAL_HPP
