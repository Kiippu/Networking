/**
 * @file simple_client.h
 * @author kory smith
 * @brief following this video https://www.youtube.com/watch?v=W9b9SaGXIjA&list=PLhnN2F9NiVmAMn9iGB_Rtjs3aGef3GpSm&index=2
 * @version 0.1
 * @date 2023-12-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <arpa/inet.h>

class simple_client
{
public:
    enum Block : u_long{
        Yes,
        No
    };
private:
    struct sockaddr_in m_srv;
    struct timeval m_time_val;
    fd_set m_read;
    fd_set m_write;
    fd_set m_exception;
    int m_port;
    Block m_isBlockingSocket;
public:
    simple_client(int port, Block isBlocking)
        : m_port(port), m_time_val{1,0}, m_isBlockingSocket(isBlocking) {};

    int Init();

    int InitSocket(int sock);

    void Send();
};