#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout << "usage: ./server <ip:port>" << endl;
        return 0;
    }
    string ipport = argv[1];
    string ip = ipport.substr(0, ipport.find(':'));
    int port = stoi(ipport.substr(ipport.find(':') + 1));
    cout << ip << " " << port << endl;
    string portip = argv[1];
    int sockfd = 0;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
    {
        printf("Fail to create a socket.");
    }

    //socket的連線

    struct sockaddr_in info;
    bzero(&info, sizeof(info));
    info.sin_family = PF_INET;

    //localhost test
    info.sin_addr.s_addr = inet_addr(ip.c_str());
    info.sin_port = htons(port);

    int err = connect(sockfd, (struct sockaddr *)&info, sizeof(info));
    if (err == -1)
    {
        printf("Connection error");
    }

    //Send a message to server
    char message[] = {"Hi there"};
    char receiveMessage[100] = {};
    send(sockfd, message, sizeof(message), 0);
    recv(sockfd, receiveMessage, sizeof(receiveMessage), 0);

    printf("%s", receiveMessage);
    printf("close Socket\n");
    return 0;
}