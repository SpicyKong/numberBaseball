실행 방법:
    RegiServer.exe를 먼저 실행 한 뒤, Peer.exe들을 실행하면 됩니다.

게임 진행:
    1. RegiServer.exe 실행 후 포트 입력
    2. 피어의 포트, 서버 아이피, 포트를 차례대로 입력
    3. online_users로 온라인 피어 확인
    4. connect 아이피 포트 명령으로 피어 연결
    5. answer 피어아이디 3자리 숫자로 정답 지정
    6. 모두 지정했으면 guess 로 게임 진행
    7. 새로운 피어와도 반복

개발 환경:
    운영체제: 윈도우 10
    컴파일러: g++.exe (Rev11, Built by MSYS2 project) 12.2.0

빌드 방법:
    Makefile이 있는 디렉토리 내에서 make 명령어를 실행하면 됩니다. (mingw가 설치되어 있어야 합니다.)

시간이 촉박해서 보다 자세한 리드미는 하단 링크에 적겠습니다.
https://github.com/SpicyKong/numberBaseball