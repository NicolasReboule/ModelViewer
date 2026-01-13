/*
** EPITECH PROJECT, 2026
** obj_loader_tests.cpp
** File description:
** obj_loader_tests.cpp
*/

#include <gtest/gtest.h>

#include "ModelManager.hpp"

TEST(ModelManager, Readiness) {
    model_viewer::ModelManager manager;
    manager.setReady(false);
    ASSERT_EQ(manager.isReady(), false)
        << "Model Manager is ready when it should not be";
    ASSERT_EQ(manager.isLoading(), true)
        << "Model Manager is not loading when it should be";
    manager.setReady(true);
    ASSERT_EQ(manager.isReady(), true)
        << "Model Manager is not ready when it should not be";
    ASSERT_EQ(manager.isLoading(), false)
        << "Model Manager is loading when it should not be";
}

TEST(ModelManager, Loaders) {
    model_viewer::ModelManager manager;
    ASSERT_EQ(manager.getLoaders().contains(".obj"), true);
    ASSERT_NE(manager.getLoaders().at(".obj"), nullptr) << "OBJ Loader is null";
    ASSERT_EQ(manager.getLoaders().contains(".uzdbh "), false);
    ASSERT_EQ(manager.getLoaders().size(), 1)
        << "Loaders map size is incorrect";
}

TEST(ModelManager, LoadersInitialization) {
    model_viewer::ModelManager mgr;

    const auto &loaders = mgr.getLoaders();
    auto it = loaders.find(".obj");
    ASSERT_NE(it, loaders.end())
        << "'.obj' loader not found in ModelManager::_loaders";

    model_viewer::loaders::ILoader *il = it->second;
    ASSERT_NE(il, nullptr) << "Loader pointer for '.obj' is null";

    // Ensure the pointer is actually an ObjLoader instance (points to internal
    // _objLoader)
    auto *objPtr = dynamic_cast<model_viewer::loaders::ObjLoader *>(il);
    ASSERT_NE(objPtr, nullptr) << "'.obj' loader is not an ObjLoader instance";
}
