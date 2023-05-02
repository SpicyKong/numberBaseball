#include "Peer.h"
#include <conio.h> // 표준이 아님
#include <thread>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
void Peer::consolePrint(char* msg) {
    consoleHideBuf();
    std::cout << msg << "\n";
    consolePrintBuf();
    // 라인 지우기
    // 새로 출력하기
    // 기존 버퍼 내용 붙여넣기
}

void Peer::consoleHideBuf() {
    printf("\r");
    for (int i=0; i<bufLeft.size() + bufRight.size(); i++) {
        std::cout << " ";
    }/*
    std::cout << "\n";*/
    std::cout << "\r";
}

void Peer::consolePrintBuf() {
    for (auto it = bufLeft.begin(); it != bufLeft.end(); it++)
        std::cout << *it;
    for (auto it = bufRight.begin(); it != bufRight.end(); it++)
        std::cout << *it;
    consoleSyncCursor();
}

void Peer::consoleSyncCursor() {
    for (int i=0; i<bufRight.size(); i++)
        std::cout << (char)8;
}

void Peer::consoleInput() {
    /*
        백스페이스, delete, 커서 구현 해야함
    */
    char key;
    while (state) {
        key = _getch();
        switch (key)
        {
        case 3: // ctrl c
            state = 0;
            break;
        case 13: // Enter key
            processBuffer();
            break;
        case 8: // back space
            if (bufLeft.size() == 0)
                continue;
            consoleHideBuf();
            bufLeft.pop_back();
            consolePrintBuf();
            break;
        case 75: // left key
            if (bufLeft.size() == 0)
                continue;
            bufRight.push_front(bufLeft.back());
            bufLeft.pop_back();
            consoleHideBuf();
            consolePrintBuf();
            break;
        case 72: // up key
            break;
        case 77: // right key
            if (bufRight.size() == 0)
                continue;
            bufLeft.push_back(bufRight.front());
            bufRight.pop_front();
            std::cout << bufLeft.back();
            //putc(*(bufLeft.end()), stdin);
            break;
        case 80: // down key
            break;
        case 83: //delete
            if (bufRight.size() == 0)
                continue;
            consoleHideBuf();
            bufRight.pop_front();
            consolePrintBuf();
            break;
        default:
            if (key < 32 || key > 127)
                continue;
            bufLeft.push_back(key);
            consoleHideBuf();
            consolePrintBuf();
            break;
        }
    }
}

void Peer::getWord(char* buf) {
    buf[0] = '\0';
    int i=0;
    while (!bufLeft.empty()) {
        if (bufLeft.front() == ' ' || bufLeft.front() == '\0') {
            buf[i] = '\0';
            return;
        }
        buf[i++] = bufLeft.front();
        bufLeft.pop_front();
    }
    while (!bufRight.empty()) {
        if (bufRight.front() == ' ' || bufRight.front() == '\0') {
            buf[i] = '\0';
            return;
        }
        buf[i++] = bufRight.front();
        bufRight.pop_front();
    }
    buf[i] = '\0';
}

void Peer::clearBuf() {
    while (!bufLeft.empty())
        bufLeft.pop_back();
    while (!bufRight.empty())
        bufRight.pop_back();
}

void Peer::processBuffer() {
    std::cout << "\n\n";
    char command[1024];
    getWord(command);
    std::cout << command << "\n";
    int l=0, r=0;

    if (strcmp(command, "help") == 0) {
        std::cout << "help: lookup all command" << "\n";
        std::cout << "online_users: get a list of all online peers from regi-server" << "\n";
        std::cout << "connect [ip] [port]: request to play a game with the given [IP] and [port]" << "\n";
        std::cout << "disconnect [peer] : end your game session with the listed [peer]" << "\n";
        std::cout << "guess [peer] [your guessing number] : send a [guessing number] to the [peer]" << "\n";
        std::cout << "answer [peer] [answer to the guess] : set a answer number to the game which playing with [peer]" << "\n";
        std::cout << "logoff : send a message to regiServer for logging off " << "\n\n";
    }
    else if (strcmp(command, "online_users") == 0) {
        std::cout << "online_users\n";
        // 패킷 매니저한테 패킷 생성 부탁
        // 네트워크한테 서버로 패킷 전송
        // 받아옴
        // 받은 값 출력
    }
    else if (strcmp(command, "connect") == 0) {
        std::cout << "connect\n";
        //l = r+1;
        //for (; r<bufIdx && buf[r]!=' ' && buf[r]!='\0'; r++);
        // IP값 저장
        // 유효성 검사 후 실패시 거짓 리턴
        // PORT 값 저장
        // 유효성 검사후 실패 시 거짓 리턴
        // 패킷 매니저로 IP port로 패킷 생성
        // 네트워크 한테 피어로 전송 부탁
    }
    else if (strcmp(command, "disconnect") == 0) {
        std::cout << "disconnect\n";
        // 네트워크 매니저가 peer와 IP port 모두 
    }
    else if (strcmp(command, "guess") == 0) {
        std::cout << "guess\n";
        // Game 한테 peer Id의 게임이 지금 내 턴인지 물어봄
        // 아니면 종료
        // guess 값 저장 및 유효성 검사
        // 패킷 생성
        // 네트워크 매니저에게 피어한테 보내라 함
    }
    else if (strcmp(command, "answer") == 0) {
        std::cout << "answer\n";
        // Game한테 게임 진행중인지 물어봄
        // 진행중이면 종료
        // answer값 저장 및 유효성 검사
        // 패킷 생성
        // 네트워크 매니저에게 준비 완료 메시지 전송

    }
    else if (strcmp(command, "logoff") == 0) {
        std::cout << "answer\n";
        // 패킷 생성
        // 네트워크 매니저에게 전송 요청
    }
    else { // 예외
        std::cout << "Your input is something wrong. If you want to know all command using help.\n";
    }
    clearBuf();
}

Peer::Peer() {
    //memset(buf, '\0', sizeof(buf));
    state = 1;
    //GM = new GameManager();
    //NM = new NetworkManager();
    //PM = new ProtocolManager();

}

Peer::~Peer() {
    //delete GM
    //delete NM
    //delete PM
}

void Peer::run() {
    std::thread _t1(consoleInput, this);
    while (state) {
        _sleep(1000);
        this->consolePrint("It's just test code.");
    }
    _t1.join();
}

int main() {
    Peer test = Peer();
    test.run();
}