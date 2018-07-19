#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "BWOExperiment.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    // For testing purpose
    // see output in debug console
    BWOExperiment experiment;
    experiment.start();

    return app.exec();
}
