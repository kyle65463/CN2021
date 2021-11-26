#include "socket.hpp"

class ClientSocket : public Socket
{
public:
    ClientSocket(int port, const string& ip) : Socket(port, ip){};

    Connection *makeConnection()
    {
        int err = connect(socketfd, (struct sockaddr *)&info, sizeof(info));
        Connection *conn = new Connection(socketfd, err == -1);
        return conn;
    }
};