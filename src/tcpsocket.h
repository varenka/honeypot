#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "color.h"

using namespace std;

class TCPSocket
{
public:
    void Init();
    TCPSocket();
    TCPSocket(string, int);
    TCPSocket(int);

    void OpenSocket(string, int);
    void ListenOnPort(int);
    void CloseSocket();
    void WriteToSocket(string);
    string ReadFromSocket();

    //port number
    unsigned int m_portNo;
    //is the connection currently open?
    bool connected;

    int GetLastError() { return m_lastError; }

    virtual ~TCPSocket();
private:
    int m_lastError;
    struct sockaddr_in serv_addr, cli_addr;
    struct hostent *server;
    //socket identifiers, m_sockFd for this socket and m_newSockFd for accepted connections
    int m_sockFd;
    int m_newSockFd;
    //the number of pending connections allowed
    int m_backLog;
    //fd set
    fd_set fds;
};

#endif // TCPSOCKET_H
