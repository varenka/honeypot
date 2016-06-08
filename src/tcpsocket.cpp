#include "tcpsocket.h"

void TCPSocket::Init()
{
    connected = false;
    m_sockFd = -1;
    m_backLog = 5;
}

TCPSocket::TCPSocket()
{
    Init();
}

TCPSocket::TCPSocket(string address, int port)
{
    Init();
    OpenSocket(address, port);
}

TCPSocket::TCPSocket(int port)
{
    Init();
    ListenOnPort(port);
}

TCPSocket::~TCPSocket()
{
    CloseSocket();
    connected = false;
}

void TCPSocket::OpenSocket(string address, int port)
{
    //create socket
    m_sockFd = socket(AF_INET, SOCK_STREAM, 0);

    //error checking
    if(m_sockFd < 0)
    {
        cout << Color::errorText("Could not open socket.") << endl;
    }

    cout << "Opening socket at FD: " << Color::intText(m_sockFd) << endl;
    cout << "Connecting with socket " << Color::intText(m_sockFd) << " to " << io::ipAddrToString(address, port) << endl;

    //resolving hostname
    server = gethostbyname(address.c_str());

    //error checking
    if(server == NULL)
    {
        cout << Color::errorText("Could not resolve hostname: ") << address << endl;
    }

    //zeroing out serv_addr
    bzero((char *) &serv_addr, sizeof(serv_addr));

    //set socket family type to internet
    serv_addr.sin_family = AF_INET;

    //copy server address to serv_addr socket
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    //convert port number to network order, add to server addr socket
    serv_addr.sin_port = htons(port);

    //connect to serv_addr
    int connectError = connect(m_sockFd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(connectError < 0)
    {
        cout << Color::errorText("Could not connect to ") << io::ipAddrToString(address, port) << endl;
        cout << Color::errorText("Error code: ") << connectError << endl;
        connected = false;
    }
    else
    {
        cout << "Connected to " << io::ipAddrToString(address, port) << endl;
        connected = true;
    }
}

void TCPSocket::ListenOnPort(int port)
{
    //create socket
    m_sockFd = socket(AF_INET, SOCK_STREAM, 0);

    //error checking
    if(m_sockFd < 0)
    {
        cout << Color::errorText("Could not open socket.") << endl;
    }

    cout << "Opening listen socket on port " << Color::ipAddrText(port) << endl;
    bzero((char *) &serv_addr, sizeof(serv_addr));

    //socket family is internet
    serv_addr.sin_family = AF_INET;
    //socket will accept connections from any address
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    //assign port number
    serv_addr.sin_port = htons(port);

    if(bind(m_sockFd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        cout << Color::errorText("Could not bind socket.") << endl;
    }

    /* listen(sockfd, backlog), where backlog is the number of pending connections that can exist before
    the socket starts responding with ECONNREFUSED */
    listen(m_sockFd, m_backLog);

    socklen_t clilen;
    clilen = sizeof(cli_addr);
    //m_newSockFd = accept(m_sockFd, (struct sockaddr *) &cli_addr, &clilen);
    //m_newSockFd = select(m_sockFd, &fds, )
    /*if(m_newSockFd < 0)
    {
        cout << Color::errorText("Could not accept incoming connection.") << endl;
    }*/

}

/* this method is called whenever a TCPSocket object is destroyed,
    but can also be used to explicitly close a connection */
void TCPSocket::CloseSocket()
{
    cout << "Closing socket at FD: " << Color::intText(m_sockFd) << endl;
    close(m_sockFd);
}

void TCPSocket::WriteToSocket(string message)
{
    m_lastError = write(m_sockFd, message.c_str(), sizeof(message.c_str()));

    if(m_lastError < 0)
    {
        cout << "Could not write to socket." << endl;
    }
}

string TCPSocket::ReadFromSocket()
{
    char* buffer = new char[512];
    m_lastError = read(m_sockFd, buffer, 511);

    if(m_lastError < 0)
    {
        cout << "Could not read from socket." << endl;
    }
    return io::ToString(buffer);
}
