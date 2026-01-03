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

class ModelManager final : public QObject {
    Q_OBJECT
    Q_PROPERTY(QQuick3DGeometry *geometry READ geometry NOTIFY geometryChanged)
    Q_PROPERTY(model_viewer::material::MTLMaterial *material READ material
                   NOTIFY materialChanged)
    Q_PROPERTY(bool loading READ isLoading NOTIFY loadingChanged)
    Q_PROPERTY(bool ready READ isReady NOTIFY readyChanged)
   public:
   private:
    loaders::ObjLoader _objLoader;

    std::unordered_map<std::string, loaders::ILoader *> _loaders = {
        {".obj", &_objLoader},
    };

    loaders::ILoader *_lastLoaded = &_objLoader;

    std::unique_ptr<geometry::ObjGeometry> _geometry;

    bool _loading = false;

    bool _ready = false;

   signals:
    void geometryChanged();

    void materialChanged();

    void loadingChanged();

    void readyChanged();

   public:
    explicit ModelManager(QObject *parent = nullptr);

    ~ModelManager() override = default;

    QQuick3DGeometry *geometry() const { return _lastLoaded->geometry(); };

    material::MTLMaterial *material() const { return _lastLoaded->material(); };

    Q_INVOKABLE void loadModel(const QString &filepath);

    bool isLoading() const { return _loading; };

    void setLoading(bool isLoading);

    bool isReady() const { return _ready; };

    void setReady(bool isReady);
};

}  // namespace model_viewer

#endif  // MODELVIEWER_MODELMANAGER_HPP
