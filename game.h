#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QtQml>
#include "coin.h"

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QPair<int, int> size, QObject *parent = 0);
    ~Game();

    Q_PROPERTY(QQmlListProperty<Coin> coins READ coins CONSTANT)
    QQmlListProperty<Coin> coins();

    Q_PROPERTY(bool live READ isLive WRITE setLive NOTIFY liveChanged)
    bool isLive() const;

    Q_PROPERTY(bool firstPlayerTurn READ isFirstPlayerTurn WRITE setFirstPlayerTurn NOTIFY firstPlayerTurnChanged)
    bool isFirstPlayerTurn() const;
signals:
    void liveChanged();
    void firstPlayerTurnChanged();
    void gameEnded(QVariant winner);
public slots:
    void setLive(bool state);
    void setFirstPlayerTurn(bool state);

    void newGame();
    void endGame(Coin::Owner winner);
    void drop(int index);
    bool didPlayerWin(int index);
    bool isNextDropPossible();
private:
    QList<Coin *> listCoins;
    QPair<int, int> boardSize;

    bool live;
    bool firstPlayerTurn;

    bool hasLine(int start, int end, int step, Coin::Owner owner);
};

#endif // GAME_H
