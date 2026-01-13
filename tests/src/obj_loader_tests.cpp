/*
** EPITECH PROJECT, 2026
** obj_loader_tests.cpp
** File description:
** obj_loader_tests.cpp
*/

#include <gtest/gtest.h>

#include "Loaders/Obj/ObjLoader.hpp"

#define CAT_VERTICES_COUNT 211728
#define CAT_NORMALS_COUNT 211728
#define CAT_TEXTURE_COORDS_COUNT 211728
#define CAT_FACES_COUNT 211728

class ObjLoaderTester : public testing::Test {
   protected:
    void SetUp() override {
        teapotLoader.loadModel("assets/teapot.obj");
        catLoader.loadModel("assets/Cat/Cat.obj");
    };

    friend model_viewer::loaders::ObjLoader;
    model_viewer::loaders::ObjLoader teapotLoader;
    model_viewer::loaders::ObjLoader catLoader;
};

TEST(ObjLoaderTest, ModelLoadingFileFound) {
    model_viewer::loaders::ObjLoader loader;
    ASSERT_EQ(loader.loadModel("assets/teapot.obj"), true) << "File not found";
}

TEST(ObjLoaderTest, ModelLoadingFileNotFound) {
    model_viewer::loaders::ObjLoader loader;
    ASSERT_EQ(loader.loadModel(""), false) << "File found";
}

TEST_F(ObjLoaderTester, VerticseCount) {
    ASSERT_EQ(catLoader.getVertices().size(), CAT_VERTICES_COUNT)
        << "Vertices count is incorrect";
}

TEST_F(ObjLoaderTester, NormalsCount) {
    ASSERT_EQ(catLoader.getNormals().size(), CAT_NORMALS_COUNT)
        << "Normals count is incorrect";
}

TEST_F(ObjLoaderTester, TextureCoordsCount) {
    ASSERT_EQ(catLoader.getTextureCoords().size(), CAT_TEXTURE_COORDS_COUNT)
        << "Texture Coordinates count is incorrect";
}

TEST_F(ObjLoaderTester, FacesCount) {
    ASSERT_EQ(catLoader.getFaces().size(), CAT_FACES_COUNT)
        << "Faces count is incorrect";
}
