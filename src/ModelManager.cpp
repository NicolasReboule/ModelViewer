/*
** EPITECH PROJECT, 2025
** ModelManager.cpp
** File description:
** ModelManager.cpp
*/

#include "ModelManager.hpp"

#include <iostream>

ModelManager::ModelManager(QObject *parent) : QObject(parent) {}

void ModelManager::loadModel(const QString &filepath) {
    const std::string str_path =
        filepath.toStdString().substr(sizeof("file://") - 1);
    const auto pos = str_path.find_last_of('.');
    const std::string ext = str_path.substr(pos);

    auto result = QtConcurrent::run([&, str_path, ext] {
        setLoading(true);
        _loaders[ext]->loadModel(str_path);
        emit geometryChanged();
        _lastLoaded = _loaders[ext];
        setLoading(false);
    });
}

void ModelManager::setLoading(bool isLoading) {
    _loading = isLoading;
    emit loadingChanged();
}
