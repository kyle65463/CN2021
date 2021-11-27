#include "socket.hpp"

class ServerSocket : public Socket
{
public:
    ServerSocket(int port) : Socket(port){};

    void startListening()
    {

        int bindErr = bind(socketfd, (struct sockaddr *)&info, sizeof(info));
        if (bindErr == -1)
            cout << "binding error" << endl;
        int listenErr = listen(socketfd, 10);
        if (listenErr == -1)
            cout << "listening error" << endl;
        if (bindErr == -1 || listenErr == -1)
            exit(-1);
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