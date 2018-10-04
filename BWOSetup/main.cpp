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
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);    // attributes that change the behavior of application-wide features
                                                                    // Enables high-DPI scaling in Qt on supported platforms
    QApplication app(argc, argv);   // manages the GUI application's control flow and main settings, init application

    // Attaching QML back-end

    qmlRegisterType<BWOExpModel>("BWOModel", 1, 0, "BWOExpModel");  // registers the C++ type in the QML system with the BWOExpModel name in the
                                                                    // library imported from BWOModel 1.0; which registers the type T=BWOExpModel as a new type
                                                                    // register the type BWOExpModel
                                                                    // under the url "BWOModel" in version 1.0
                                                                    // under the name "BWOExpModel"
    BWOExpModel dataModel;
    BWOExperiment bwoExperiment(&dataModel);

    QQuickView viewer;  // provides a window for displaying a Qt Quick user interface
    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);
        // engine() - Returns a pointer to the QQmlEngine used for instantiating QML Components.
        // quit - This signal is emitted when the QML loaded by the engine would like to quit.
        // QQuickView inherits QWindow, clos() -> Close the window.

    viewer.rootContext()->setContextProperty("dataModel", &dataModel);
        // returns the root of the context hierarchy as QQmlContext.
        // setContextProperty -> Set the dataModel of the "dataModel" property on this context.

    QUrl source = QUrl("qrc:/qml/main.qml");

    viewer.setTitle(QStringLiteral("Backward Wave Oscillator (BWO)"));
    viewer.setSource(source);   // Sets the source to the url, loads the QML component and instantiates it.
    viewer.setResizeMode(QQuickView::SizeRootObjectToView); // SizeRootObjectToView - the view will automatically resize the root item to the size of the view.

    QObject *item = viewer.rootObject();    // Returns the view's root item.

    QObject::connect(item, SIGNAL(startButtonClicked()), &bwoExperiment, SLOT(start()));
    QObject::connect(item, SIGNAL(stopButtonClicked()), &bwoExperiment, SLOT(stop()));
    QObject::connect(item, SIGNAL(setButtonClicked()), &bwoExperiment, SLOT(set()));
    QObject::connect(item, SIGNAL(openFolderClicked()), &bwoExperiment, SLOT(openFolder()));

    viewer.show();

    return app.exec();  // execute event loop
}
