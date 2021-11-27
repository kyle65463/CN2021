#include <iostream>
#include <sys/socket.h>
#define HEADER_SIZE 16
using namespace std;

class Connection
{
public:
    Connection(int fd, bool hasError = false) : fd(fd), hasError(hasError) {}

    void sendMessage(const string &msg, int size = -1)
    {
        if(size == -1)
            size = msg.size() + 1;
        send(fd, msg.c_str(), size, 0);
    }

    string recvMessage(int size = -1)
    {
        char buf[256] = {};
        if (size == -1)
            size = sizeof(buf);
        int ret = recv(fd, buf, size, 0);
        if (ret <= 0)
        {
            isDisconnected = true;
            closeConnection();
        }
        return string(buf);
    }

    void sendFile(const string &filename)
    {
        FILE *fp = fopen(filename.c_str(), "rb");
        int bytes_read;
        char buffer[1024];
        fseek(fp, 0L, SEEK_END);
        int filelen = ftell(fp);
        fseek(fp, 0L, SEEK_SET);

        sendMessage(to_string(filelen), HEADER_SIZE);
        while (!feof(fp))
        {
            if ((bytes_read = fread(&buffer, 1, 1024, fp)) > 0) {
                send(fd, buffer, bytes_read, 0);
            }
            else
                break;
        }
        fclose(fp);
    }

    void recvFile(const string &outname)
    {
        size_t datasize = 1;
        FILE *filefd = fopen(outname.c_str(), "wb");
        int length = stoi(recvMessage(HEADER_SIZE));
        while (length > 0)
        {
            char text[1024];
            datasize = recv(fd, text, sizeof(text), 0);
            length -= datasize;
            fwrite(&text, 1, datasize, filefd);
        }
        fclose(filefd);
    }

    void login(const string &username)
    {
        this->username = username;
        isLoggedIn = true;
    }

    void closeConnection()
    {
        close(fd);
    }

    // Getters
    int getFd() { return fd; }
    bool getHasError() { return hasError; }
    bool getIsDisconnected() { return isDisconnected; }
    bool getIsLoggedIn() { return isLoggedIn; }
    const string &getUsername() { return username; }

private:
    int fd;
    bool hasError;
    bool isDisconnected;
    bool isLoggedIn;
    string username;
};