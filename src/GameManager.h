#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H
#include <map>
#include "Game.h"

class GameManager {
private:
    std::map<int, Game*> gameList;
    int digit;
public:
    GameManager();
    ~GameManager();
    bool createGame(int opponentId);
    bool setAnswer(int opponentId, int answer);
    void deleteGame(int opponentId);
    bool getState(int opponentId);
    int submitGuess(int opponentId, int guess);

};

#endif

/*
    Game 
    - 게임 생성
    - 게임 삭제
    - 상태 확인
    - 답안 제출 (여기 결과에 따라 게임 삭제 가능)
*/