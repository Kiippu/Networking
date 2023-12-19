#include "simple_server.h"
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

int simple_server::Init()
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
    m_srv.sin_addr.s_addr = INADDR_ANY;                 // make os decide address of home
    // m_srv.sin_addr.s_addr = inet_addr("127.0.0.1");  // this is also acceptable for specific address
    memset(&(m_srv.sin_zero), 0, 8);                    // init this char?? why??

    /**
     * @brief set blocking or non blocking. by default it is blocking
     * @param __fd         the socket to configure
     * @param __request    Sets or clears nonblocking input/output for a socket
     * @param ...          set to either 0 for blocking or !0 for non blocking
     */
    auto ret = ioctl(sock, FIONBIO, &m_isBlockingSocket);
    if(ret < 0){
        std::cout << "ioctl has failed" << std::endl;
        return state::FAIL;
    }
    else
        std::cout << "ioctl has succeeded with a " 
            << (m_isBlockingSocket?"non-blocking": "blocking")
            << " socket" << std::endl;

    /**
     * @brief           
     * @param __fd      
     * @param __addr    
     * @param __len     
     */
    int optVal = 0;
    int optLen = sizeof(optVal);
    // setting this is not asvided as other processes can hijack socket
    ret = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char const *)&optVal, optLen);
    // ret = setsockopt(sock, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (char const *)&optVal, optLen);
    if(ret < 0){
        std::cout << "setsockopt failed" << std::endl;
        return state::FAIL;
    }
    else
        std::cout << "setsockopt successful" << std::endl;

    /**
     * @brief           bind the socket to the local port
     * @param __fd      the socket int
     * @param __addr    the address settings
     * @param __len     the length of the settings in bytes
     */
    ret = bind(sock, (sockaddr*)&m_srv, sizeof(sockaddr));
    if(ret < 0){
        std::cout << "socket has failed to bind to port" << std::endl;
        return state::FAIL;
    }
    else
        std::cout << "socket has successfully bind to the port" << std::endl;

    /**
     * @brief       listen to the requests from clients
     * @param __fd  the socket to listen on
     * @param __n   the max number of requests to have in queue prior to refusal of requests
     */
    ret = listen(sock, 5);
    if(ret < 0){
        std::cout << "socket has failed to listen to port" << std::endl;
        return state::FAIL;
    }
    else
        std::cout << "socket has successfully started listen to the port" << std::endl;

    // wait for new requests as per request
    ret = InitSocket(sock);
    while (ret >= 0)
    {
        if (ret > 0)
        {
            // we have communications on our socket do something
            std::cout << "there is data in the sockets!" << std::endl;

            if (FD_ISSET(sock, &m_exception))
            {
                /* code */
            }

            if (FD_ISSET(sock, &m_write))
            {
                /* code */
            }

            if (FD_ISSET(sock, &m_read))
            {
                /* code */
            }
        }
        else if (ret == 0)
        {
            // we have no communications on our sockets so sleep for 2 seconds
            std::cout << "we have no communications on our sockets.. " << std::endl;
            sleep(2);
        }
        else
        {
            // we have an error in our socket setup
            std::cout << "we have an error in our socket setup. " << std::endl;
            break;
        }
        


        ret = InitSocket(sock);
    }
    
    
    

    return state::SUCCESS;
}

int simple_server::InitSocket(int sock)
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