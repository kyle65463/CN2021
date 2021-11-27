#include <iostream>
#include <sys/socket.h>
using namespace std;

class Connection
{
public:
    Connection(int fd, bool hasError = false) : fd(fd), hasError(hasError) {}

    void sendMessage(const string &msg)
    {
        send(fd, msg.c_str(), msg.size(), 0);
    }

    string recvMessage()
    {
        char buf[256] = {};
        int ret = recv(fd, buf, sizeof(buf), 0);
        if (ret <= 0)
        {
            disconnected = true;
            closeConnection();
        }
        return string(buf);
    }

    void sendFile(const string &filename)
    {
        FILE *filefd = fopen(filename.c_str(), "rb");
        int bytes_read;
        char buffer[1024];
        while (!feof(filefd))
        {
            if ((bytes_read = fread(&buffer, 1, 1024, filefd)) > 0)
                send(fd, buffer, bytes_read, 0);
            else
                break;
        }
        fclose(filefd);
    }

    void recvFile(const string &outname)
    {
        size_t datasize = 1;
        FILE *filefd = fopen(outname.c_str(), "wb");
        while (datasize > 0)
        {
            char text[1024];
            datasize = recv(fd, text, sizeof(text), 0);
            fwrite(&text, 1, datasize, filefd);
        }
        fclose(filefd);
    }

    void closeConnection()
    {
        close(fd);
    }

    // Getters
    int getFd() { return fd; }
    bool getHasError() { return hasError; }
    bool getDisconnected() { return disconnected; }

private:
    int fd;
    bool hasError;
    bool disconnected;
};