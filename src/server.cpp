#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "usage: ./server <port>" << endl;
        return 0;
    }
    int port = stoi(argv[1]);
    cout << "hi " << port << endl;
    int serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocketFd == -1)
    {
        cout << "Could not open socket" << endl;
    }
    //socket的連線
    struct sockaddr_in serverInfo;
    bzero(&serverInfo, sizeof(serverInfo));

    serverInfo.sin_family = PF_INET; // ipv4
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(port);
    bind(serverSocketFd, (struct sockaddr *)&serverInfo, sizeof(serverInfo));

    listen(serverSocketFd, 5);

    while (1)
    {
        struct sockaddr_in clientInfo;
        unsigned int addrlen = sizeof(clientInfo);
        int clientSocketFd = accept(serverSocketFd, (struct sockaddr *)&clientInfo, &addrlen);
        cout << clientSocketFd << endl;
        char inputBuffer[256] = {};
        char message[] = {"Hi,this is server.\n"};
        send(clientSocketFd, message, sizeof(message), 0);
        recv(clientSocketFd, inputBuffer, sizeof(inputBuffer), 0);
        printf("Get:%s\n", inputBuffer);
        close(clientSocketFd);
    }
    return 0;
}