#include <iostream>
#include <WinSock2.h>
#include <vector>
#include <string>
#pragma comment(lib, "Ws2_32.lib")

int answer = 456, digit = 3;
/*struct TEST{
    int a, b;
};
void funct(char* tmp)
{
    hh(tmp);
}

void hh(char* tmp)
{
    ((TEST*)tmp)->a = 456;
    ((TEST*)tmp)->b = 456;
}*/

int getStrike(int guess)
{
    int count = 0, tmp_guess=guess, tmp_answer=answer;
    for (int i=0; i<digit; i++) 
    {
        if (tmp_guess%10 == tmp_answer%10) 
            ++count;
        tmp_answer/=10;
        tmp_guess/=10;
    }
    return count;
}

int getBall(int guess)
{
    int count = 0, tmp_guess=guess, tmp_answer=answer, chk=0;
    for (int i=0; i<digit; i++) 
    {
        tmp_guess = guess;
        chk=0;
        for (int j=0; j<digit; j++) 
        {
            if (tmp_answer%10 == tmp_guess%10)
            {
                if (i==j)
                {
                    chk=0;
                    break;
                }
                else
                    chk=1;
            }
            tmp_guess /= 10;
        }
        count += chk;
        tmp_answer /= 10;
    }
    return count;
}

int main()
{   
    int a;
    std::cin >> a;
    std::cout << getStrike(a) << " " << getBall(a) << "\n";
    /*
    TEST test{1, 1};
    std::cout << test.a << " " << test.b << "\n";
    funct((char*)&test);
    std::cout << test.a << " " << test.b << "\n";*/
    //std::string line = "111", tmp="1a1";
    //std::cout << checkNum(line, 5) << " " << checkNum(tmp, 5) << "\n";
    /*std::vector<std::string> words;
    for (char a : line)
    {
        if (a == ' ' || a=='\0')
        {
            words.push_back(tmp);
            tmp="";
        }
        else
        {
            tmp+=a;
        }
    }
    for (std::string a : words)
    {
        std::cout << a << "\n";
    }*/
    return 0;
}

/*
    If you want to compile this, you should linking ws2_32 lib.
    how? 
    gcc test.c -lws2_32 
    
  help: \n
        lookup command (display all possible commands and their description)\n
\n
  online_users: \n
        send a request to the regiServer, get back a list of all online peers and display them on the screen\n
\n
  connect [ip] [port]: \n
        request to play a game with the given IP and port\n
\n
  disconnect [peer] : \n
        end your game session with the listed peer\n
\n
  guess [peer] [your guessing number] : \n
        send a guessing number to the peer that you've already initiated a game with via the \"connect\" command \n
\n
  answer [peer] [answer to the guess] : \n
        send a response to guessing number.\n
\n
  logoff : send a message (notification) to regiServer for logging off\n
*/