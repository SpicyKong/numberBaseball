#include "Peer.h"
#include <cstring>
#include <thread>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include "Packet.h"
#include "tools.cpp"

Peer::Peer(int myPort)
{
    port = myPort;
    nm = new NetworkManager(myPort); // myPort 리스닝 소켓 포트
    gm = new GameManager();
    nm->setMediator(this);
    cli = new Cli();
    cli->setMediator(this);
    state = 1;
}

Peer::~Peer()
{
    state = 0;
    delete gm, nm, cli;

}

void Peer::notify(std::string event, int id)
{
    if (event == "KEY_PRESS") 
    {
        //cli->consolePrint("key is pressed");
        std::string line = cli->getLine(), tmp="", msg="", v="";
        std::vector<std::string> words;
        for (char a : line)
        {
            if (a == ' ')
            {
                words.push_back(tmp);
                tmp="";
            }
            else
            {
                tmp+=a;
            }
        }
        words.push_back(tmp);
        if (words[0] == "help")
        {
            cli->consolePrint("  help: \n        lookup command (display all possible commands and their description)\n\n  online_users: \n        send a request to the regiServer, get back a list of all online peers and display them on the screen\n\n  connect [ip] [port]: \n        request to play a game with the given IP and port\n\n  disconnect [peer] : \n        end your game session with the listed peer\n\n  guess [peer] [your guessing number] : \n        send a guessing number to the peer that you've already initiated a game with via the \"connect\" command \n\n  answer [peer] [answer to the guess] : \n        send a response to guessing number.\n\n  logoff : send a message (notification) to regiServer for logging off\n");
        }
        else if (words[0] == "online_users")
        {
            HEADER myHeader{0, 13, peerId};
            nm->writeData(serverSock, (char*)&myHeader, sizeof(HEADER));
            // 서버한테 요청
        }
        else if (words[0] == "connect")
        {
            //words1 = ip, words2 = port
            if (words.size() < 3)
            {
                msg = "[Service] Usage: connect [ip] [port]";
            }
            else
            {
                //size, hId, peerId
                int sock = nm->createSocket(words[1].c_str(), words[2].c_str());
                HEADER myHeader{0, 0, peerId};
                nm->writeData(sock, (char*)&myHeader, sizeof(myHeader));
                
                if (sock == 0)
                {
                    msg = "[Service] connecting to ";
                }
                v = ":";
                v = words[1] + v + words[2];
            }
            cli->consolePrint(msg + v);
        }
        else if (words[0] == "disconnect")
        {
            if (words.size() < 2) 
            {
                msg = "[Service] Usage: disconnect [peer]";
            }
            else
            {
                if (checkNum(words[1], 5) == 0)
                {
                    msg = "[Service] PEER ID must consist of number.";
                }
                else
                {
                    int pid = std::stoi(words[1]);
                    if (peer2sock.find(pid) == peer2sock.end()) // 해당 피어가 없으면
                    {
                        msg = "[Service] The connection is not exist.";
                    }
                    else
                    {
                        HEADER myHeader{0, 15, peerId};
                        nm->writeData(pid, (char*)&myHeader, sizeof(myHeader));
                    }
                }
            }
            cli->consolePrint(msg);
        }
        else if (words[0] == "guess")
        {
            if (words.size() < 3) 
            {
                msg = "[Service] Usage: guess [peer] [your guessing number]";
            }
            else
            {
                if (checkNum(words[1], 5) == 0)
                {
                    msg = "[Service] PEER ID must number.)";
                }
                else if (checkNum(words[2], 3) == 0)
                {
                    msg = "[Service] GUESS must satisfy 0 <= GUESS <= 999)";
                }
                else if (gm->getState(std::stoi(words[1])) == -1)
                {
                    msg = "[Service] The game is not exist";
                }
                else
                {
                    //std::cout << gm->getState(std::stoi(words[1])) << "\n";
                    if (gm->getState(std::stoi(words[1])) < 3)// 상대 혹은 내가 ans설정 안한 상황
                    {
                        msg = "[Service] You or your peer should set ANSWER before guessing.";
                    }
                    else
                    {
                        GAMEBODY gmBody{-1, -1, std::stoi(words[2]), -1};//int endId, errId, guess, res;
                        HEADER myHeader{sizeof(gmBody), 7, peerId};
                        //std::cout << "bonem\n";
                        if (gm->isMyTurn(std::stoi(words[1])))
                        {
                            nm->writeData(peer2sock[std::stoi(words[1])], (char*)&myHeader, sizeof(myHeader));
                            nm->writeData(peer2sock[std::stoi(words[1])], (char*)&gmBody, sizeof(gmBody));
                            gm->countTrun(std::stoi(words[1]));
                            //return;
                        }
                        else
                        {
                            msg = "[Service] It's not your turn now.";
                        }
                    }
                }
            }
            cli->consolePrint(msg);
        }
        else if (words[0] == "answer")
        {
            if (words.size() < 3) 
            {
                msg = "[Service] Usage: answer [peer] [answer to the guess] ";
            }
            else
            {
                if (checkNum(words[1], 5) == 0)
                {
                    msg = "[Service] PEER ID must number.)";
                }
                else if (checkNum(words[2], 3) == 0)
                {
                    msg = "[Service] ANSWER must satisfy 0 <= ANSWER <= 999)";
                }
                else
                {
                    int pid = std::stoi(words[1]), ans=std::stoi(words[2]);
                    if (gm->getState(pid) > 1)
                    {
                        msg = "[Service] ANSWER is already set.";
                    }
                    else
                    {
                        gm->setState(pid, 2);
                        gm->setAnswer(pid, ans);
                        HEADER myHeader{0, 5, peerId};
                        nm->writeData(peer2sock[pid], (char*)&myHeader, sizeof(myHeader));
                        std::string s1="[peer", s2=std::to_string(pid), s3="] ", s4;
                        if (gm->getState(pid) >= 3)
                        {
                            if (gm->isMyTurn(pid))
                                s4 = " your turn is now.";
                            else
                                s4 = " your turn is next.";
                            cli->consolePrint(s1 + s2 + s3 + s4);
                        }
                        //return;
                    }
                }
            }
            cli->consolePrint(msg);
        }
        else if (words[0] == "logoff")
        {
            // 서버 연결 끊기
            // 위에서 서버가 끊기면 종료가 되도록 만들어서 
            // 해당 명령시 그냥 미리 종료.
            exit(0);
        }
        else
        {
            cli->consolePrint("Check your input. You can see command list using help.");
        }

    }
    else if (event == "STOP") 
    {
        cli->consolePrint(std::string("stopped"));
        state = 0;
    }
    else if (event == "TEST")
    {
        cli->consolePrint(std::string("Done"));
    }
    else if (event == "SOCK_MESSAGE")
    {
        
        HEADER packetHeader{-1, -1, -1}, myHeader;
        if (nm->recvData(id, (char*)&packetHeader, sizeof(packetHeader)) <= 0)
        {
            nm->shutdownSocket(id);
            if (id == serverSock)
            {
                cli->consolePrint("[Server] server is closed. Try re-starting this program.");
                exit(-1);
                return;
            }
            else 
            {
                std::string s1="The connection is closed with peer", s2=std::to_string(sock2peer[id]);
                cli->consolePrint(s1+s2);
                gm->deleteGame(sock2peer[id]);
                peer2sock.erase(sock2peer[id]);
                sock2peer.erase(id);
            }
        }
        int s, b;
        //std::cout << "OPPONENT IP: " << getIp(id) << ":" << getPort(id) << "\n";
        //std::cout << packetHeader.hId << " " << packetHeader.peerId << " " << packetHeader.size << "\n";
        std::string s1 = "[peer", s2=std::to_string(packetHeader.peerId), s3 = "] ", s4, s5, s6, s7; // dirty code..
        GAMEBODY gmBody, gmBodyIn, gmBodyOut;
        switch (packetHeader.hId)
        {
            case 0:
                peer2sock[packetHeader.peerId] = id;
                sock2peer[id] = packetHeader.peerId;
                myHeader = {0, 1, peerId};
                nm->writeData(id, (char*)&myHeader, sizeof(myHeader));
                gm->createGame(packetHeader.peerId, 0);
                
                s4 = "Connected! Set your answer!";
                cli -> consolePrint(s1  + s2 + s3 + s4);
                // 여기서 바로 게임 셋업 ㄱ 얘가 후공
                break;
            case 1:
                peer2sock[packetHeader.peerId] = id;
                sock2peer[id] = packetHeader.peerId;
                gm->createGame(packetHeader.peerId, 1);
                
                s4 = "Connected! Set your answer.";
                cli -> consolePrint(s1 + s2 + s3 + s4);
                // 여기서 바로 게임 셋업 ㄱ 얘가 선공
                break;
            case 2:
                // ping 전송 => 필요 없음
                //myHeader = {0, 3, peerId};
                //nm->writeData(id, (char*)&myHeader);
                break;
            case 3:
                // ping 수신=> 필요 없음
                break;
            case 4:
                // 만약 게임 존재하면 무시 => 필요 없음
                // [없앨놈] 그냥 0, 1 에서 게임 생성함
                // gm->createGame(packetHeader.peerId, 0);
                // + 생성 관련
                break;
            case 5:
                // 상대 등록
                s4="set asnwer.";
                cli->consolePrint(s1 + s2 + s3 + s4);
                gm->setState(packetHeader.peerId, 1);

                if (gm->getState(packetHeader.peerId) >= 3)
                {
                    if (gm->isMyTurn(packetHeader.peerId))
                        s4 = " your turn is now.";
                    else
                        s4 = " your turn is next.";
                    cli->consolePrint(s1 + s2 + s3 + s4);
                }
                break;
            case 6:
                gmBody = {-1, -1, -1, -1};
                nm->recvData(id, (char*)&gmBody, sizeof(gmBody));
                if (gmBody.errId == ERR_NOT_YOUR_TURN)
                {
                    cli->consolePrint("[GAME] Your turn is not yet.");
                }
                else if (gmBody.errId == ERR_NOT_SETUP)
                {
                    cli->consolePrint("[GAME] All participant should set GUESS befroe starting a game.");
                }
                else
                {
                    cli->consolePrint("[GAME] undefined error occured.");
                }
                break;
            case 7:
                gmBodyOut = {-1, -1, -1, -1}; // endId, errId, guess, res;
                nm->recvData(id, (char*)&gmBodyIn, sizeof(gmBodyIn));
                if (gm->isMyTurn(packetHeader.peerId))
                {
                    // 너 턴 아님
                    gmBodyOut.errId = ERR_NOT_YOUR_TURN;
                    myHeader = {sizeof(gmBodyOut), 6, peerId};
                    nm->writeData(id, (char*)&myHeader, sizeof(myHeader));
                    nm->writeData(id, (char*)&gmBodyOut, sizeof(gmBodyOut));
                }
                else
                {
                    // 결과 계산후 전송
                    gm->countTrun(packetHeader.peerId);
                    gmBodyOut.res = gm->submitGuess(packetHeader.peerId, gmBodyIn.guess);
                    int s = (gmBodyOut.res/10)%10, b = gmBodyOut.res%10;
                    std::cout << gmBodyIn.guess << " " << s << " " << b << "<= guess\n";
                    myHeader = {sizeof(gmBodyOut), 8, peerId};
                    nm->writeData(id, (char*)&myHeader, sizeof(myHeader));
                    nm->writeData(id, (char*)&gmBodyOut, sizeof(gmBodyOut));
                    // all strike면 게임 끝
                    s4 = "sent a guess.";
                    cli->consolePrint(s1 + s2 + s3 + s4);
                    if (s>=3)
                    {
                        myHeader = {0, 9, peerId};
                        gmBodyOut = {-1, -1, -1, -1};
                        gmBodyOut.endId = GAME_YOU_WIN;
                        nm->writeData(id, (char*)&myHeader, sizeof(myHeader));
                        nm->writeData(id, (char*)&gmBodyOut, sizeof(gmBodyOut));
                        s4 = "You lose. The game is end.";
                        cli->consolePrint(s1 + s2 + s3 + s4);
                        // 커넥션 종료
                    }
                }
                break;
            case 8:
                {
                    nm->recvData(id, (char*)&gmBody, sizeof(gmBody));
                    int s = (gmBody.res/10)%10;
                    s4=std::to_string((gmBody.res/10)%10), s5="strike, ", s6 = std::to_string(gmBody.res%10), s7="ball.";
                    cli->consolePrint(s1 + s2 + s3 + s4 + s5 + s6 + s7);
                    if (s >= 3)
                    {
                        gm->deleteGame(packetHeader.peerId);
                        nm->shutdownSocket(id);
                    }
                }
                break;
            case 9: // 게임 종료 메시지
                nm->recvData(id, (char*)&gmBody, sizeof(gmBody));
                gm->deleteGame(packetHeader.peerId);
                nm->shutdownSocket(id);

                s4 = "game is closed.";
                cli->consolePrint(s1 + s2 + s3 + s4);
                break;
            case 11: // login 응답 받음
                peerId = packetHeader.peerId;
                s1="Hello. Your peer number is ";
                s2 = std::to_string(peerId);
                cli->consolePrint(s1 + s2);
                break;
            case 14: // 유저 목록 받음
                {

                    USERINFO user;
                    std::string s1="[", s2, s3="] ", s4, s5=":", s6;
                    cli->consolePrint("Online User List\n==================");
                    while (packetHeader.size > 0)
                    {
                        nm->recvData(id, (char*)&user, sizeof(user));
                        s2 = std::to_string(user.peerId);
                        //std::cout << s2 << "<== ip\n";
                        s4 = ip2str(user.ip);
                        s6 = std::to_string(user.port);
                        cli->consolePrint(s1 + s2 + s3 + s4 + s5 + s6);
                        packetHeader.size -= (int)sizeof(USERINFO);
                    }
                }
                break;
            case 15:
                nm->shutdownSocket(id);
                break;
            default:
                break;
        }
    }
}
/*
    hId(header id list)
    00: 안녕 난 peer1인데 넌 누구니?
    01: 안녕 peer1반가워 난 peer2야
    02: 저기요? 살아있나요?
    03: 네 살아있어요

    04: 나랑 게임 셋업할래?
    05: 나는 준비가 다 되었어
    06: 무슨말인지 모르겠어(ex. 아직 guess설정 안함, 지금 네 턴 아니야)
    07: 현재턴, 나의 guess 는 xxx야
    08: 그래 너의 xxx는 1s, 1b이야
    09: 우리 게임 종료하자(사유)

    10: 서버야 나 왔어
    11: 서버야 나 갈게
    13: 서버야 유저 목록을 알려줘
    14: 유저목록 여기 (헤더에서 전체 사이즈 알려줌)

    15: 우리 이만 연결 종료하자
*/


#include <iostream>
void Peer::run(std::string serverIp, std::string serverPort)
{
    
    std::thread consoleInterface(Cli::run, cli);
    std::thread networkListening(NetworkManager::startListen, nm);
    
    if ((serverSock = nm->createSocket(serverIp.c_str(), serverPort.c_str())) < 0)
    {
        throw "Failed to connect to the server!";
    }
    HEADER login{sizeof(USERINFO), 10, -1};
    
    if (nm->writeData(serverSock, (char*)&login, sizeof(login)) < 0)
    {
        throw "Failed to connect to the server.\n";
    }
    USERINFO user{-1, port, ip2int(serverIp)}; // 어차피 내 소켓 모두 아이피 동일하니
    nm->writeData(serverSock, (char*)&user, sizeof(USERINFO));

    consoleInterface.join();
    networkListening.join();
}

std::mutex GameManager::m;

int main() {
    std::string ip="127.0.0.1", port="5000";
    std::cout << "Your   Port: ";
    std::cin >> port;
    Peer test = Peer(std::stoi(port));
    std::cout << "Server   IP: ";
    std::cin >> ip;
    std::cout << "Server Port: ";
    std::cin >> port;
    test.run(ip, port);
}
// 서버와의 연결이 끊긴 경우 피어 재접속 알림 => X
// 피어 연결 종료시 알림 => 해결
// 127.0.0.0? =>
// 게임 종료 후 피어 정보 정상 종료 해야함 => 해결
// 시작 턴 말해줌
// 끝내고 It's not 뜨는거