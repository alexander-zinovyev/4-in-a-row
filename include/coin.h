#ifndef COIN_H
#define COIN_H

#include <QObject>

class Coin : public QObject
{
    Q_OBJECT

public:
    explicit Coin(QObject *parent = 0);
    enum Owner {
        None = 0, FirstPlayer, SecondPlayer
    };
    Q_ENUMS(Owner)

    Q_PROPERTY(Owner owner READ getOwner WRITE setOwner NOTIFY ownerChanged)
    Owner getOwner() const;

    bool hasOwner() const;
public slots:
    void setOwner(Owner owner);
signals:
    void ownerChanged();
private:
    Owner owner;
};

#endif // COIN_H
