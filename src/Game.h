#ifndef _GAME_H
#define _GAME_H
class Game {
private:
    int opponentId, answer, digit;
public:
    Game(int opponentId, int digit);
    void setAnswer(int ans);
    int getStrike(int guess);
    int getBall(int guess);
    bool getState();
};
#endif
/*
    게임에서 필요한 것 들:
    - 생성자: 상대
    - answer 등록
    - guess 채점
    - 게임 상태 반환
*/