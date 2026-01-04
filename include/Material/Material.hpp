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

/**
 * @brief Class representing a material parsed from an MTL file
 * @todo Seek ways to improve this class' architecture
 */
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
    //! Parent path of the MTL file
    std::filesystem::path _parentPath;

    //! Ambient Color
    QColor _Ka;

    //! Diffuse Color
    QColor _Kd;

    //! Specular Color
    QColor _Ks;

    //! Emissive Color
    QColor _Ke;

    //! Transmission Filter
    QColor _Tf;

    //! Illumination Model
    qreal _illumination;

    //! Opacity
    qreal _d;

    //! Specular Roughness
    qreal _Ns;

    //! Sharpness
    qreal _sharpness;

    //! Index of Refraction
    qreal _Ni;

    //! Metalness
    qreal _metalness = 0.0;

    //! Roughness
    qreal _roughness = 0.0;

    //! Bump/Normal Strength
    qreal _bumpStrength = 0.0;

    //! Path to the Ambient Map
    QUrl _ambientMap;

    //! Path to the Diffuse Map
    QUrl _diffuseMap;

    //! Path to the Specular Reflection Map
    QUrl _specularReflectionMap;

    //! Path to the Specular Map
    QUrl _specularMap;

    //! Path to the Emissive Map
    QUrl _emissiveMap;

    //! Path to the Dissolve Map
    QUrl _dissolveMap;

    //! Path to the Bump/Normal Map
    QUrl _bumpMap;

    //! Path to the Decal Map
    QUrl _decalMap;

    //! Path to the Dispersion Map
    QUrl _dispersionMap;

    //! Maps to store parsed values before applying them
    std::unordered_map<std::string, qreal> _scalars;

    //! Maps to store parsed colors before applying them
    std::unordered_map<std::string, QColor> _colors;

    //! Maps to store parsed texture maps before applying them
    std::unordered_map<std::string, QUrl> _maps;

    //! Map of parsing functions for different MTL line prefixes
    std::unordered_map<std::string, std::function<void(const std::string &,
                                                       const std::string &)>>
        _parseFunctions;

   public:
    /**
     * @brief Constructor
     * @param parent Parent QObject, nullptr by default
     */
    explicit MTLMaterial(QObject *parent = nullptr);

    //! Destructor
    ~MTLMaterial() override = default;

    /**
     * @brief Parse an MTL file and set the material properties
     * @param filepath Path to the MTL file
     */
    void parseMTL(const std::string &filepath);

    //! Reset the material to default values
    void resetMaterial();

    /**
     * @brief Get the Ambient Map URL
     * @return Ambient Map URL
     */
    const QUrl &getAmbientMap() const { return _ambientMap; };

    /**
     * @brief Get the Diffuse Map URL
     * @return Diffuse Map URL
     */
    const QUrl &getDiffuseMap() const { return _diffuseMap; };

    /**
     * @brief Get the Specular Reflection Map URL
     * @return Specular Reflection Map URL
     */
    const QUrl &getSpecularReflectionMap() const {
        return _specularReflectionMap;
    };

    /**
     * @brief Get the Specular Map URL
     * @return Specular Map URL
     */
    const QUrl &getSpecularMap() const { return _specularMap; };

    /**
     * @brief Get the Emissive Map URL
     * @return Emissive Map URL
     */
    const QUrl &getEmissiveMap() const { return _emissiveMap; };

    /**
     * @brief Get the Dissolve Map URL
     * @return Dissolve Map URL
     */
    const QUrl &getDissolveMap() const { return _dissolveMap; };

    /**
     * @brief Get the Bump/Normal Map URL
     * @return Bump/Normal Map URL
     */
    const QUrl &getBumpMap() const { return _bumpMap; };

    /**
     * @brief Get the Decal Map URL
     * @return Decal Map URL
     */
    const QUrl &getDecalMap() const { return _decalMap; };

    /**
     * @brief Get the Dispersion Map URL
     * @return Dispersion Map URL
     */
    const QUrl &getDispersionMap() const { return _dispersionMap; };
   signals:
    //! Signal emitted when the diffuse color changes
    void KdChanged();

    //! Signal emitted when the illumination model changes
    void illuminationChanged();

    //! Signal emitted when the opacity changes
    void dChanged();

    //! Signal emitted when the specular roughness changes
    void NsChanged();

    //! Signal emitted when the sharpness changes
    void sharpnessChanged();

    //! Signal emitted when the index of refraction changes
    void NiChanged();

    //! Signal emitted when the metalness changes
    void metalnessChanged();

    //! Signal emitted when the roughness changes
    void roughnessChanged();

    //! Signal emitted when the bump strength changes
    void bumpStrengthChanged();

    //! Signal emitted when the diffuse map changes
    void diffuseMapChanged();

    //! Signal emitted when the specular reflection map changes
    void specularReflectionMapChanged();

    //! Signal emitted when the specular map changes
    void specularMapChanged();

    //! Signal emitted when the emissive map changes
    void emissiveMapChanged();

    //! Signal emitted when the dissolve map changes
    void dissolveMapChanged();

    //! Signal emitted when the bump map changes
    void bumpMapChanged();

   private:
    //! Apply parsed values to the material properties
    void setMaterialValues();

    /**
     * @brief Parse a scalar value from an MTL line
     * @param line Line to parse
     * @param key Key of the scalar value
     */
    void parseScalar(const std::string &line, const std::string &key);

    /**
     * @brief Parse a color value from an MTL line
     * @param line Line to parse
     * @param key Key of the color value
     */
    void parseColor(const std::string &line, const std::string &key);

    /**
     * @brief Parse a texture map from an MTL line
     * @param line Line to parse
     * @param key Key of the texture map
     */
    void parseMap(const std::string &line, const std::string &key);
};

}  // namespace model_viewer::material

#endif  // MODELVIEWER_MATERIAL_HPP
