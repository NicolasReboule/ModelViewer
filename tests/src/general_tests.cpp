//
// Created by nicol on 29/12/2024.
//

#include <gtest/gtest.h>

#include "ModelManager.hpp"

TEST(Coverage, TouchAllClasses) {
    const model_viewer::loaders::ObjLoader loader;
    const model_viewer::geometry::ObjGeometry geometry;
    const model_viewer::material::MTLMaterial material;
    const model_viewer::ModelManager manager;

    SUCCEED();
}