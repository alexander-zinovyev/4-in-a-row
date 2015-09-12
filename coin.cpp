#include "coin.h"

Coin::Coin(QObject *parent) : QObject(parent), owner(Owner::None) {

}

Coin::Owner Coin::getOwner() const {
    return owner;
}

bool Coin::hasOwner() const {
    return owner != Owner::None;
}

void Coin::setOwner(Owner owner) {
    if (this->owner == owner)   return;
    this->owner = owner;
    emit ownerChanged();
}
