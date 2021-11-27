#include "socket.hpp"

class ClientSocket : public Socket
{
public:
    ClientSocket(int port, const string &ip) : Socket(port, ip){};

    Connection *makeConnection()
    {
        int err = connect(socketfd, (struct sockaddr *)&info, sizeof(info));
        if (err < 0)
            hasError = true;
        Connection *conn = new Connection(socketfd);
        return conn;
    }
};