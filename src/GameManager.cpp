#include "GameManager.h"

GameManager::GameManager()
{
    digit = 3;
}

GameManager::~GameManager()
{
    for (auto i = gameList.begin(); i!=gameList.end(); i++) 
    {
        delete i->second;
    }
    gameList.clear();
}

bool GameManager::createGame(int opponentId, int myTurn)
{
    if (gameList.find(opponentId) != gameList.end())
    {
        return 0;
    }
    Game* newGame = new Game(opponentId, digit, myTurn);
    gameList[opponentId] = newGame;
    return 1;
}

bool GameManager::setAnswer(int opponentId, int answer)
{
    if (gameList.find(opponentId) == gameList.end())
        return 0;
    gameList[opponentId]->setAnswer(answer);
    return 1;
}

void GameManager::deleteGame(int opponentId)
{
    if (gameList.find(opponentId) != gameList.end())
        delete gameList[opponentId];
}

int GameManager::getState(int opponentId)
{
    if (gameList.find(opponentId) != gameList.end())
        return gameList[opponentId]->getState();
    return -1;
}

void GameManager::setState(int opponentId, int d)
{
    if (gameList.find(opponentId) != gameList.end())
        gameList[opponentId]->setState(d);
}

/*
    두 자리 십진수 SB, S: 스트라이크 수, B 볼 수
*/
#include <iostream>
int GameManager::submitGuess(int opponentId, int guess)
{
    if (gameList.find(opponentId) == gameList.end())
    {
        return -1;
    }
    int count_s=gameList[opponentId]->getStrike(guess), count_b=gameList[opponentId]->getBall(guess);
    if (count_s == digit)
    {
        deleteGame(opponentId);
        return 30;
    }
    return count_s*10 + count_b;
}

bool GameManager::isMyTurn(int opponentId)
{
    if (gameList.find(opponentId) == gameList.end())
    {
        return 0;
    }
    return (gameList[opponentId]->getTurn())%2;
}

bool GameManager::countTrun(int opponentId)
{
    m.lock();
    if (gameList.find(opponentId) == gameList.end())
    {
        m.unlock();
        return 0;
    }
    gameList[opponentId]->countTurn();
    m.unlock();
    return 1;
}