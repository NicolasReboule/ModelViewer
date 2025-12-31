/*
** EPITECH PROJECT, 2025
** ModelManager.hpp
** File description:
** ModelManager.hpp
*/

#ifndef MODELVIEWER_MODELMANAGER_HPP
#define MODELVIEWER_MODELMANAGER_HPP

#include <QtConcurrent/QtConcurrentRun>

#include "ObjLoader.hpp"

class ModelManager final : public QObject {
    Q_OBJECT
    Q_PROPERTY(QQuick3DGeometry *geometry READ geometry NOTIFY geometryChanged)
    Q_PROPERTY(bool loading READ isLoading NOTIFY loadingChanged)
    Q_PROPERTY(bool ready READ isReady NOTIFY readyChanged)
   public:
   private:
    ObjLoader _objLoader;

    std::unordered_map<std::string, ILoader *> _loaders = {
        {".obj", &_objLoader},
    };
    ILoader *_lastLoaded = &_objLoader;

    std::unique_ptr<ObjGeometry> _geometry;

    bool _loading = false;

    bool _ready = false;

   signals:
    void geometryChanged();

    void loadingChanged();

    void readyChanged();

   public:
    explicit ModelManager(QObject *parent = nullptr);

    ~ModelManager() override = default;

    QQuick3DGeometry *geometry() const { return _lastLoaded->geometry(); };

    Q_INVOKABLE void loadModel(const QString &filepath);

    bool isLoading() const { return _loading; };

    void setLoading(bool isLoading);

    bool isReady() const { return _ready; };

    void setReady(bool isReady);
};

#endif  // MODELVIEWER_MODELMANAGER_HPP
