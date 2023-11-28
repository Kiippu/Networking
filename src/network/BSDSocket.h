#pragma once
#include <string>


class BSDSocket
{
private:
    const std::string m_ip; 
    const int m_port;
public:
    BSDSocket(std::string ip, int port);
};