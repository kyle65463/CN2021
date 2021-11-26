#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "connection.hpp"
using namespace std;

class Socket {
public:
    Socket(int port, const string& ip = "") {
        socketfd = socket(AF_INET, SOCK_STREAM, 0);
        in_addr_t s_addr = ip.size() == 0 ? INADDR_ANY : inet_addr(ip.c_str());
        bzero(&info, sizeof(info));
        info.sin_family = PF_INET;
        info.sin_addr.s_addr = s_addr;
        info.sin_port = htons(port);
    }

    virtual Connection *makeConnection() = 0;

protected:
    struct sockaddr_in info;
    int socketfd;
};