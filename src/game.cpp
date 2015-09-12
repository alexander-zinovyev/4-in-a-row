#include "include/game.h"

Game::Game(QPair<int, int> size, QObject *parent) :
    QObject(parent),
    boardSize(size),
    live(false),
    firstPlayerTurn(true)
{
    for (int i = 0; i < boardSize.first * boardSize.second; i++) {
        listCoins << new Coin;
    }
}

Game::~Game() {
    qDeleteAll(listCoins);
    listCoins.clear();
}

void Game::newGame() {
    for (auto item : listCoins)
        item->setOwner(Coin::Owner::None);

    setLive(true);
    setFirstPlayerTurn(true);
}

void Game::endGame(Coin::Owner winner) {
    setLive(false);

    emit gameEnded(winner);
}

void Game::drop(int index) {
    if (!isLive())  return;

    //get lowest possible coin in the column (which has no owner)
    int column = index % boardSize.first;
    int lowestCoinIndex = column;
    for (int i = column; i < boardSize.first * boardSize.second; i += boardSize.first) {
        Coin *temp = listCoins.at(i);
        if (temp && temp->getOwner() == Coin::Owner::None)
            lowestCoinIndex = i;
    }

    Coin *coin = listCoins.at(lowestCoinIndex);
    if (!coin || coin->getOwner() > Coin::Owner::None)
        return;

    Coin::Owner currentPlayer = isFirstPlayerTurn() ? Coin::Owner::FirstPlayer : Coin::Owner::SecondPlayer;
    coin->setOwner(currentPlayer);

    //did player win after this coindrop?
    if (didPlayerWin(lowestCoinIndex)) {
        endGame(currentPlayer);
        return;
    }

    setFirstPlayerTurn(!isFirstPlayerTurn());

    //if there are no free fields available AND player didn't win after this drop - game ended in a draw
    if (!isNextDropPossible()) {
        endGame(Coin::Owner::None);
        return;
    }
}

bool Game::didPlayerWin(int index) {
    Coin::Owner currentPlayer = (isFirstPlayerTurn()) ? Coin::Owner::FirstPlayer : Coin::Owner::SecondPlayer;

    //Player wins the game if there are 4 straight coins that belongs to currentPlayer

    //Check row
    int start = index - index % boardSize.first,
        end = start + boardSize.first - 1;

    int step = 1;

    if (hasLine(start, end, step, currentPlayer))
        return true;

    //Check column
    start = index % boardSize.first;
    end = boardSize.first * (boardSize.second - 1) + start;
    step = boardSize.first;

    if (hasLine(start, end, boardSize.first, currentPlayer))
        return true;

    //Check diagonals
    //calculating index offsets
    int leftOffset = index % boardSize.first,
        rightOffset = boardSize.first - leftOffset - 1,
        topOffset = index / boardSize.first,
        bottomOffset = boardSize.second - topOffset - 1;

    //upper left to bottom right
    step = boardSize.first + 1;
    int minOffset = qMin(leftOffset, topOffset);
    start = index - minOffset * step;

    minOffset = qMin(rightOffset, bottomOffset);
    end = index + minOffset * step;

    if (hasLine(start, end, step, currentPlayer))
        return true;

    //upper right to bottom left
    step = boardSize.first - 1;
    minOffset = qMin(rightOffset, topOffset);
    start = index - minOffset * step;

    minOffset = qMin(leftOffset, bottomOffset);
    end = index + minOffset * step;

    if (hasLine(start, end, step, currentPlayer))
        return true;

    return false;
}

bool Game::isNextDropPossible() {
    //Next drop is not possible, if there aren't any free fields in the first row
    for (int i = 0; i < boardSize.first; i++) {
        Coin *temp = listCoins.at(i);
        if (temp && temp->getOwner() == Coin::Owner::None)
            return true;
    }
    return false;
}

bool Game::hasLine(int start, int end, int step, Coin::Owner owner) {
    int coinsInARow = 0;
    Coin *temp = NULL;

    for (int i = start; i <= end; i += step) {
        temp = listCoins.at(i);
        if (temp && temp->getOwner() == owner)
            coinsInARow++;
        else
            coinsInARow = 0;

        if (coinsInARow == 4)   return true;
    }
    return false;
}

//getters & setters
QQmlListProperty<Coin> Game::coins() {
    return QQmlListProperty<Coin>(this, listCoins);
}

bool Game::isLive() const {
    return live;
}

bool Game::isFirstPlayerTurn() const {
    return firstPlayerTurn;
}

void Game::setLive(bool state) {
    if (this->live == state)    return;
    this->live = state;
    emit liveChanged();
}

void Game::setFirstPlayerTurn(bool state) {
    if (this->firstPlayerTurn == state) return;
    this->firstPlayerTurn = state;
    emit firstPlayerTurnChanged();
}
