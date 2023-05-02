enum class PacketHeader {
    REQ_PING,
    RES_PING,
    REQ_LOGIN,
    RES_LOGIN, // body: peerId
    REQ_LOGOUT,
    REQ_USERS, // userList
    RES_USERS,
    REQ_GAME_READY,
    REQ_GAME_START,
    REQ_GAME_GUESS,
    RES_GAME_ANS,
    REQ_GAME_CLOSE
};

struct packet
{
    unsigned int pSize;
    short header;
    int body;
};
