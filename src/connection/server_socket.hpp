#include "socket.hpp"

class ServerSocket : public Socket
{
public:
    ServerSocket(int port) : Socket(port) {};

    Connection* makeConnection()
    {
        bind(socketfd, (struct sockaddr *)&info, sizeof(info));
        listen(socketfd, 10);

        struct sockaddr_in clientInfo;
        unsigned int clientInfoLen = sizeof(clientInfo);
        int clientSocketFd = accept(socketfd, (struct sockaddr *)&clientInfo, &clientInfoLen);
        Connection* conn = new Connection(clientSocketFd);
        return conn;
    }
};