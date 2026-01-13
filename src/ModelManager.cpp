/*
** EPITECH PROJECT, 2025
** ModelManager.cpp
** File description:
** ModelManager.cpp
*/

#include "ModelManager.hpp"

#include <iostream>

namespace model_viewer {

ModelManager::ModelManager(QObject *parent) : QObject(parent) {
    _loaders = {
        {".obj", &_objLoader},
    };
}

void ModelManager::loadModel(const QString &filepath) {
    const std::string strPath =
        filepath.toStdString().substr(sizeof("file://") - 1);
    const auto pos = strPath.find_last_of('.');
    const std::string ext = strPath.substr(pos);

    auto result = QtConcurrent::run([&, strPath, ext] {
        setReady(false);
        _loaders[ext]->loadModel(strPath);
        emit geometryChanged();
        emit materialChanged();
        _lastLoaded = _loaders[ext];
        setReady(true);
    });
}

void ModelManager::setLoading(const bool isLoading) {
    _loading = isLoading;
    emit loadingChanged();
}

void ModelManager::setReady(const bool isReady) {
    _ready = isReady;
    emit readyChanged();
    setLoading(!isReady);
}

}  // namespace model_viewer