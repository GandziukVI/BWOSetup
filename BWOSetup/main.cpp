#include <QtWidgets/QApplication>
#include <QtQuick/QQuickItem>
#include <QtQuick/QQuickView>
#include <QtCore/QDir>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>

#include "BWOExperiment.h"
#include "qmlBackEnd/BWOExpModel.h"

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    // Attaching QML back-end

    qmlRegisterType<BWOExpModel>("BWOModel", 1, 0, "BWOExpModel");

    BWOExpModel dataModel;
    BWOExperiment bwoExperiment(&dataModel);

    QQuickView viewer;
    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);

    viewer.rootContext()->setContextProperty("dataModel", &dataModel);

    QUrl source = QUrl("qrc:/qml/main.qml");

    viewer.setTitle(QStringLiteral("Backward Wave Oscillator (BWO)"));
    viewer.setSource(source);
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);

    QObject *item = viewer.rootObject();

    QObject::connect(item, SIGNAL(startButtonClicked()), &bwoExperiment, SLOT(start()));
    QObject::connect(item, SIGNAL(stopButtonClicked()), &bwoExperiment, SLOT(stop()));

    viewer.show();

    // For testing purpose
    // see output in debug console


    return app.exec();
}
