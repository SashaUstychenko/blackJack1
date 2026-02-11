#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "controlerblackjack.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<ControlerBlackJack>("blackJack", 1, 0, "ControlerBlackJack");

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("blackJack", "Main");

    return app.exec();
}
