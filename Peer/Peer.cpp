#include "Peer.h"
#include <conio.h> // 표준이 아님
#include <thread>
#include <cstring>
#include <iostream>
#include <stdlib.h>

void Peer::print(char* msg) {
    if (buf[0] != '\0')
        std::cout << "\33[2K\r";
    std::cout << msg << "\n";
    if (buf[0] != '\0')
        std::cout << buf;

    // 라인 지우기
    // 새로 출력하기
    // 기존 버퍼 내용 붙여넣기
}

void Peer::input() {
    /*
        백스페이스, delete, 커서 구현 해야함
    */
    while (state) {
        buf[bufIdx++] = _getch();
        if (buf[bufIdx-1]==']')
            state = 0;
        std::cout << buf[bufIdx-1];
        buf[bufIdx] = '\0';
        if (buf[bufIdx-1] == 13) { // Enter
            processBuffer();
        }
        else if (buf[bufIdx-1] == 8) { // Backspace
            buf[bufIdx--] = '\0';
        }
    }
}

bool Peer::processBuffer() {
    std::cout << "\n";
    int l=0, r=0;
    // space, null문자, 엔터 만나기까지 반복
    for (; r<bufIdx && buf[r]!=' ' && buf[r]!='\0' && buf[r]!=13; r++);
    buf[r] = '\0';
    std::cout << buf << " ";
    if (strcmp(buf, "help") == 0) {
        std::cout << "help: lookup all command" << "\n";
        std::cout << "online_users: get a list of all online peers from regi-server" << "\n";
        std::cout << "connect [ip] [port]: request to play a game with the given [IP] and [port]" << "\n";
        std::cout << "disconnect [peer] : end your game session with the listed [peer]" << "\n";
        std::cout << "guess [peer] [your guessing number] : send a [guessing number] to the [peer]" << "\n";
        std::cout << "answer [peer] [answer to the guess] : set a answer number to the game which playing with [peer]" << "\n";
        std::cout << "logoff : send a message to regiServer for logging off " << "\n\n";
    }
    else if (strcmp(buf, "online_users") == 0) {
        std::cout << "online_users\n";
        // 패킷 매니저한테 패킷 생성 부탁
        // 네트워크한테 서버로 패킷 전송
        // 받아옴
        // 받은 값 출력
    }
    else if (strcmp(buf, "connect") == 0) {
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
    else if (strcmp(buf, "disconnect") == 0) {
        std::cout << "disconnect\n";
        // 네트워크 매니저가 peer와 IP port 모두 
    }
    else if (strcmp(buf, "guess") == 0) {
        std::cout << "guess\n";
        // Game 한테 peer Id의 게임이 지금 내 턴인지 물어봄
        // 아니면 종료
        // guess 값 저장 및 유효성 검사
        // 패킷 생성
        // 네트워크 매니저에게 피어한테 보내라 함
    }
    else if (strcmp(buf, "answer") == 0) {
        std::cout << "answer\n";
        // Game한테 게임 진행중인지 물어봄
        // 진행중이면 종료
        // answer값 저장 및 유효성 검사
        // 패킷 생성
        // 네트워크 매니저에게 준비 완료 메시지 전송

    }
    else if (strcmp(buf, "logoff") == 0) {
        std::cout << "answer\n";
        // 패킷 생성
        // 네트워크 매니저에게 전송 요청
    }
    else { // 예외
        std::cout << "Your input is something wrong. If you want to know all command using help.\n";
    }

    bufIdx = 0;
    buf[0] = '\0';
}

Peer::Peer() {
    memset(buf, '\0', sizeof(buf));
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
    std::thread _t1(input, this);
    //std::thread _t2()
    while (state) {
        _sleep(1000);
        this->print("It's just test code.");
    }
    _t1.join();
}

int main() {
    //Peer* test = new Peer();
    //test->run();
    Peer test = Peer();
    test.run();
}