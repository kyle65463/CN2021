#include "socket.hpp"

class ServerSocket : public Socket
{
public:
    ServerSocket(int port) : Socket(port){};

    void startListening()
    {

        int err = bind(socketfd, (struct sockaddr *)&info, sizeof(info));
        if (err == -1)
            cout << "binding error" << endl;
        err = listen(socketfd, 10);
        if (err == -1)
            cout << "listening error" << endl;
    }

    Connection *makeConnection()
    {
        struct sockaddr_in clientInfo;
        unsigned int clientInfoLen = sizeof(clientInfo);
        int clientSocketFd = accept(socketfd, (struct sockaddr *)&clientInfo, &clientInfoLen);
        Connection *conn = new Connection(clientSocketFd);
        return conn;
    }
};