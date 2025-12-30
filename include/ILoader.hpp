/*
** EPITECH PROJECT, 2025
** ILoader.hpp
** File description:
** ILoader.hpp
*/

#ifndef MODELVIEWER_ILOADER_HPP
#define MODELVIEWER_ILOADER_HPP

#include <QQuick3DGeometry>

class ILoader {
   public:
    virtual ~ILoader() = default;

    virtual void loadModel(const std::string &filepath) = 0;

    virtual QQuick3DGeometry *geometry() const = 0;
};

#endif  // MODELVIEWER_ILOADER_HPP
