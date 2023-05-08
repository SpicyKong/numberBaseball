#include <string>
#include <iostream>
#include <winsock2.h>
#include <string>

bool checkNum(std::string& num, int digit)
{
    if (num.length() < 1 || num.length() > digit)
        return 0;
    for (char l : num)
    {
        if (l < '0' || l > '9')
            return 0;
    }
    return 1;
}

std::string getIp(int sockId)
{
    std::string ip;
    sockaddr adr;
    int len=sizeof(adr);
    int ret = getpeername(sockId, &adr, &len);
    sockaddr_in* tmp = (sockaddr_in*)&adr;
    return inet_ntoa(tmp->sin_addr);
}

std::string getPort(int sockId)
{
    std::string ip;
    sockaddr adr;
    int len=sizeof(adr);
    int ret = getpeername(sockId, &adr, &len);
    sockaddr_in* tmp = (sockaddr_in*)&adr;
    return std::to_string(ntohs(tmp->sin_port));
}

int ip2int(std::string ip)
{
    return inet_addr(ip.c_str());
}

std::string ip2str(long long ip)
{
    in_addr tmp;
    tmp.S_un.S_addr = ip;
    return std::string(inet_ntoa(tmp));
}