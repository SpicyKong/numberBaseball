#ifndef _GAME_H
#define _GAME_H
class Game {
private:
    int opponentId, answer, digit, turn, state;
public:
    Game(int opponentId, int digit, int turn);
    void setAnswer(int ans);
    int getStrike(int guess);
    int getBall(int guess);
    int getState();
    void setState(int d);
    int getTurn();
    void countTurn();
};
#endif
/*
    게임에서 필요한 것 들:
    - 생성자: 상대
    - answer 등록
    - guess 채점
    - 게임 상태 반환
*/