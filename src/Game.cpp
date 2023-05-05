#include "Game.h"

Game::Game(int opponentId, int digit)
{
    opponentId = opponentId;
    answer = -1;
    digit = digit;
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
    int count = 0, tmp_guess=guess, tmp_answer=answer;
    for (int i=0; i<digit; i++) 
    {
        tmp_guess = tmp_guess;
        for (int j=0; j<digit; j++) 
        {
            if (i==j)
                continue;
            if (tmp_answer%10 == tmp_guess%10)
                ++count;
            tmp_guess /= 10;
        }
        tmp_answer /= 10;
    }
    return count;
}

bool Game::getState()
{
    if (answer < 0)
        return 0;
    return 1; 
}