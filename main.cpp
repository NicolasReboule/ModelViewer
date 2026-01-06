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
    QQmlApplicationEngine *engine = new QQmlApplicationEngine();
    model_viewer::ModelManager modelManager;
    engine->rootContext()->setContextProperty("ModelManager", &modelManager);
    // Cleans up engine on exit
    QObject::connect(&app, &QGuiApplication::aboutToQuit, engine,
                     &QQmlApplicationEngine::deleteLater);
    engine->loadFromModule("ModelViewerModule", "Main");
    return app.exec();
}
