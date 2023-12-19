#include "simple_client.h"
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include  <sys/ioctl.h>


enum state
{
    SUCCESS,
    FAIL
};

int simple_client::Init()
{
    /**
     * @brief           init the socket object
     * @param _domain   this is the form of socket protocol family we will use
     * @param _type     the way we plan to receive data in this socket
     * @param _protocol the protocol used in this socket
     */
    auto sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock < 0){
        std::cout << "socket has failed to open" << std::endl;
        return state::FAIL;
    }
    else
        std::cout << "socket has successfully opened" << std::endl;

    // initalized the environment for sockaddr structure
    m_srv.sin_family = AF_INET;                         //  socket protocol family
    m_srv.sin_port = htons(m_port);                     // convert to correct Endian
    m_srv.sin_addr.s_addr = inet_addr("127.0.0.1");  // this is also acceptable for specific address
    memset(&(m_srv.sin_zero), 0, 8);                    // init this char?? why??

    // connect to a server
    auto ret = connect(sock, (struct sockaddr*) & m_srv, sizeof(m_srv));
    if(ret < 0){
        std::cout << "connection to server has failed" << std::endl;
        return state::FAIL;
    }
    else
        std::cout << "connection to server has succeeded" << std::endl;

    return state::SUCCESS;
}

int simple_client::InitSocket(int sock)
{
    // clear the socket array streams
    FD_ZERO(&m_read);
    FD_ZERO(&m_write);
    FD_ZERO(&m_exception);

    // set these socket array to kernal memory
    FD_SET(sock, &m_read);
    FD_SET(sock, &m_exception);

    // get max socket
    auto max_sock = sock + 1;

    /**
     * @brief check if socket arrays are ready to be read
     * @param ____nfds      socket to check
     * @param __readfds     read array 
     * @param __writefds    write array
     * @param __exceptfds   exception array
     * @param __timeout     the time taken prior to returning
     * @return return 
     */
    return select( max_sock, &m_read, &m_write, &m_exception, &m_time_val);
}