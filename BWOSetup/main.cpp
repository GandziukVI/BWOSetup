#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtCore/QDir>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>

#include "BWOExperiment.h"

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QQuickView viewer;
    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);

    QUrl source = QUrl("qrc:/qml/main.qml");

    viewer.setTitle(QStringLiteral("Backward Wave Oscillator (BWO)"));

    viewer.setSource(source);
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.show();

    // For testing purpose
    // see output in debug console
    QObject *expSettings = new QObject();
    BWOExperiment experiment(expSettings);
    experiment.start();

    return app.exec();
}
