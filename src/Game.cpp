#include "Game.h"

Game::Game(int opponentId, int digit, int turn)
{
    this->turn = turn;
    this->opponentId = opponentId;
    this->answer = -1;
    this->digit = digit;
    state=0;
}

void Game::setAnswer(int ans)
{
    answer = ans;
    opponentId = 0;
}

int Game::getStrike(int guess)
{
    int count = 0, tmp_guess=guess, tmp_answer=answer;
    for (int i=0; i<digit; i++) 
    {
        if (tmp_guess%10 == tmp_answer%10) 
            ++count;
        tmp_answer/=10;
        tmp_guess/=10;
    }
    return count;
}

int Game::getBall(int guess)
{
    int count = 0, tmp_guess=guess, tmp_answer=answer, chk=0;
    for (int i=0; i<digit; i++) 
    {
        tmp_guess = guess;
        chk=0;
        for (int j=0; j<digit; j++) 
        {
            if (tmp_answer%10 == tmp_guess%10)
            {
                if (i==j)
                {
                    chk=0;
                    break;
                }
                else
                    chk=1;
            }
            tmp_guess /= 10;
        }
        count += chk;
        tmp_answer /= 10;
    }
    return count;
}

int Game::getState()
{
    return state;
}

void Game::setState(int d)
{
    state += d;
}

int Game::getTurn()
{
    return turn;
}

void Game::countTurn()
{
    ++turn;
}