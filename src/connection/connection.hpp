#include <iostream>
#include <sys/socket.h>
using namespace std;

class Connection
{
public:
    Connection(int fd) : fd(fd) {}

    void sendMessage(const string& msg) {
        send(fd, msg.c_str(), 256, 0);
    }

    string recvMessage() {
        char buf[256] = {};
        recv(fd, buf, sizeof(buf), 0);
        return string(buf);
    }

    void closeConnection() {
        close(fd);
    }

private:
    int fd;
};