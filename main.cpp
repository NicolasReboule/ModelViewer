#include <qqml.h>

#include <QFileInfo>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QString>

#include "Loaders/Obj/ObjLoader.hpp"
#include "Material/Material.hpp"
#include "ModelManager.hpp"

using namespace Qt::StringLiterals;

int main(int argc, char *argv[]) {
    const QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    model_viewer::ModelManager modelManager;
    engine.rootContext()->setContextProperty("ModelManager", &modelManager);
    engine.loadFromModule("ModelViewerModule", "Main");
    return app.exec();
}
