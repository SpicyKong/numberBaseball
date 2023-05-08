#define ERR_NOT_YOUR_TURN 0
#define ERR_NOT_SETUP 1

#define GAME_YOU_WIN 0

#define END_CLOSE
//#include <
struct HEADER
{
    int size, hId, peerId;
};
/*
    hId(header id list)
    00: 안녕 난 peer1인데 넌 누구니?
    01: 안녕 peer1반가워 난 peer2야
    02: 저기요? 살아있나요?
    03: 네 살아있어요

    04: 나랑 게임 셋업할래?
    05: 나는 준비가 다 되었어
    06: 게임시작하자
    07: 현재턴, 나의 guess 는 xxx야
    08: 그래 너의 xxx는 1s, 1b이야
    09: 우리 게임 종료하자(사유)

    00: 서버야 나 왔어
    11: 서버야 나 갈게
    12: 서버야 유저 목록을 알려줘
*/

struct USERINFO
{
    int peerId, port;
    int ip;
};

struct GAMEBODY
{
    int endId, errId, guess, res;
};
