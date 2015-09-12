#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "game.h"
#include "coin.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<Coin>("TestTask", 1, 0, "Coin");
    Game *game = new Game(qMakePair(7, 6));

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("game", game);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
