#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H
#include <map>
#include "Game.h"
#include <mutex>

class GameManager {
private:
    std::map<int, Game*> gameList;
    int digit;
public:
    static std::mutex m;
    GameManager();
    ~GameManager();
    bool createGame(int opponentId, int myTurn);
    bool setAnswer(int opponentId, int answer);
    bool isMyTurn(int opponentId);
    void deleteGame(int opponentId);
    int getState(int opponentId);
    void setState(int opponentId, int d);
    int submitGuess(int opponentId, int guess);
    bool countTrun(int opponentId);

};

#endif

/*
    Game 
    - 게임 생성
    - 게임 삭제
    - 상태 확인
    - 답안 제출 (여기 결과에 따라 게임 삭제 가능)
*/