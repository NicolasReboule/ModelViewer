/*
** EPITECH PROJECT, 2025
** ModelManager.hpp
** File description:
** ModelManager.hpp
*/

#ifndef MODELVIEWER_MODELMANAGER_HPP
#define MODELVIEWER_MODELMANAGER_HPP

#include <QtConcurrent/QtConcurrentRun>

#include "Loaders/Obj/ObjLoader.hpp"

namespace model_viewer {

/**
 * @brief Class for managing model loading and providing geometry and material
 */
class ModelManager final : public QObject {
    Q_OBJECT
    Q_PROPERTY(QQuick3DGeometry *geometry READ geometry NOTIFY geometryChanged)
    Q_PROPERTY(model_viewer::material::MTLMaterial *material READ material
                   NOTIFY materialChanged)
    Q_PROPERTY(bool loading READ isLoading NOTIFY loadingChanged)
    Q_PROPERTY(bool ready READ isReady NOTIFY readyChanged)
   public:
   private:
    //! OBJ loader instance
    loaders::ObjLoader _objLoader;

    //! Map of file extensions to their respective loaders
    std::unordered_map<std::string, loaders::ILoader *> _loaders = {
        {".obj", &_objLoader},
    };

    //! Pointer to the last used loader
    loaders::ILoader *_lastLoaded = &_objLoader;

    //! Geometry of the currently loaded model
    std::unique_ptr<geometry::ObjGeometry> _geometry;

    //! Boolean indicating if a model is currently loading
    bool _loading = false;

    //! Boolean indicating if a model is ready
    bool _ready = false;

   signals:
    //! Signal emitted when the geometry changes
    void geometryChanged();

    //! Signal emitted when the material changes
    void materialChanged();

    //! Signal emitted when the loading state changes
    void loadingChanged();

    //! Signal emitted when the ready state changes
    void readyChanged();

   public:
    /**
     * @brief Constructor
     * @param parent Parent QObject, nullptr by default
     */
    explicit ModelManager(QObject *parent = nullptr);

    //! Destructor
    ~ModelManager() override = default;

    /**
     * @brief Get the geometry of the loaded model
     * @return Geometry of the loaded model
     */
    QQuick3DGeometry *geometry() const { return _lastLoaded->geometry(); };

    /**
     * @brief Get the material of the loaded model
     * @return Material of the loaded model
     */
    material::MTLMaterial *material() const { return _lastLoaded->material(); };

    /**
     * @brief Load a model from a file asynchronously
     * @details Emits geometryChanged and materialChanged signals upon
     * completion and is invokable from QML
     * @param filepath Path to the model file
     */
    Q_INVOKABLE void loadModel(const QString &filepath);

    /**
     * @brief Check if a model is currently loading
     * @return True if a model is loading, false otherwise
     */
    bool isLoading() const { return _loading; };

    /**
     * @brief Set the loading state, emits loadingChanged signal
     * @param isLoading New loading state
     */
    void setLoading(bool isLoading);

    /**
     * @brief Check if a model is ready
     * @return True if a model is ready, false otherwise
     */
    bool isReady() const { return _ready; };

    /**
     * @brief Set the ready state, emits readyChanged signal
     * @param isReady New ready state
     */
    void setReady(bool isReady);
};

}  // namespace model_viewer

#endif  // MODELVIEWER_MODELMANAGER_HPP
