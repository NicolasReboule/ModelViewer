/*
** EPITECH PROJECT, 2025
** ILoader.hpp
** File description:
** ILoader.hpp
*/

#ifndef MODELVIEWER_ILOADER_HPP
#define MODELVIEWER_ILOADER_HPP

#include <QQuick3DGeometry>

#include "Material/Material.hpp"

namespace model_viewer::loaders {

/**
 * @brief Interface for model loaders
 */
class ILoader {
   public:
    //! Virtual destructor
    virtual ~ILoader() = default;

    /**
     * @brief Load a model from a file
     * @param filepath Path to the model file
     * @return Boolean indicating whether the model was loaded successfully
     */
    virtual bool loadModel(const std::string &filepath) = 0;

    /**
     * @brief Get the geometry of the loaded model
     * @return Geometry of the loaded model
     */
    virtual QQuick3DGeometry *geometry() const = 0;

    /**
     * @brief Get the material of the loaded model
     * @return Material of the loaded model
     */
    virtual material::MTLMaterial *material() const = 0;
};

}  // namespace model_viewer::loaders

#endif  // MODELVIEWER_ILOADER_HPP
